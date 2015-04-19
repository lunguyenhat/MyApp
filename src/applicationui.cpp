/*
 * Copyright (c) 2013-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"
#include "ActiveFrameQML.h"

#include "T2W API/Talk2WatchInterface.h"
#include "T2W API/UdpModule.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/system/InvokeManager>
#include <bb/device/BatteryInfo>
#include <bb/device/BatteryChargingState>
#include <bb/platform/Notification>
#include <bb/platform/NotificationGlobalSettings>
#include <bb/platform/NotificationMode>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::device;
using namespace bb::platform;

ApplicationUI::ApplicationUI(Application *app) :
        QObject(app),
        m_translator(new QTranslator(this)),
        m_localeHandler(new LocaleHandler(this)),
        m_invokeManager(new InvokeManager(this))
{
    myapp = app;
    // prepare the localization
    if (!QObject::connect(m_localeHandler, SIGNAL(systemLanguageChanged()),
            this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }

    t2w = new Talk2WatchInterface(9712, this);

    uuid << "688fe407d65c4e8cae57ee7dc3c919c2" << "5dbac19332da46059990caa467bf5478";

    batteryInfo = new BatteryInfo();
    connect(batteryInfo, SIGNAL(levelChanged(int, bb::device::BatteryChargingState::Type)), this, SLOT(onBatteryLevelChanged(int, bb::device::BatteryChargingState::Type)));

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Make app available to the qml.
    qml->setContextProperty("app", this);

    activeFrame = new ActiveFrameQML();
    myapp->setCover(activeFrame);

    qml->setContextProperty("activeFrame", activeFrame);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    myapp->setScene(root);

    connect(t2w, SIGNAL(transmissionReady()), this, SLOT(onTransmissionReady()));
    connect(t2w, SIGNAL(authSuccess()), this, SLOT(onAuthSuccess()));
    connect(t2w, SIGNAL(uuidRegistrationSuccess(QString)), this, SLOT(onUuidRegistrationSuccess(QString)));
    connect(t2w, SIGNAL(appMessageReceived(QString, QHash<QString, QVariant>)), this, SLOT(onAppMessageReceived(QString, QHash<QString, QVariant>)));

    // Create UdpModule object, open a UDP port for communicating with T2W and connect to signal
    udp = new UdpModule(this);
    udp->listenOnPort(9712); // this number should be changed to a random unused port

    notificationGlobalSettings = new NotificationGlobalSettings();
    m_notify = new Notification();
    m_notify->setTitle("MyApp");
    m_notify->setBody("Where are you?");

    connect(myapp, SIGNAL(manualExit()), this, SLOT(onManualExit()));
    myapp->setAutoExit(false);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_translator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("MyApp_%1").arg(locale_string);

    if (m_translator->load(file_name, "app/native/qm"))
    {
        QCoreApplication::instance()->installTranslator(m_translator);
    }
}

void ApplicationUI::onManualExit()
{
    foreach (QString i, uuid)
    {
        t2w->deregisterAppMessageListener(i);
    }

    myapp->quit();
}

void ApplicationUI::onTransmissionReady()
{
    qDebug() << "onTransmissionReady -- HL";

    authorizeAppWithT2w();
}

void ApplicationUI::authorizeAppWithT2w()
{
    qDebug() << "authorizeAppWithT2w";

    t2w->setAppValues("MyApp", "1.0.0", "MyApp1.0.0", "UPD", "9712", "");
    t2w->sendAppAuthorizationRequest();  // Send authorization request to T2W
}

void ApplicationUI::onAuthSuccess()
{
    qDebug() << "Auth_Success!!!";

    foreach (QString i, uuid)
    {
        t2w->registerAppMessageListener(i);
    }
}

void ApplicationUI::onUuidRegistrationSuccess(const QString &_uuid)
{
    qDebug() << "onUuidRegistrationSuccess!!!";

    if (_uuid == uuid[0])
    {
        triggerBattery(true);
    }

    myapp->minimize();
}

void ApplicationUI::onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values)
{
    qDebug() << "onAppMessageReceived";

    int value = _values.values().at(0).toInt();

    if (_uuid == uuid[0])
    {
        triggerBattery(false);
        activeFrame->updatePebbleBattery(value);
    }
    else if (_uuid == uuid[1])
    {
        if (value == 0 || value == 1)
        {
            NotificationSettingsError::Type error = NotificationSettingsError::None;

            if(value == 0)
            {
                error = notificationGlobalSettings->setMode(NotificationMode::Normal);
            }
            else if(value == 1)
            {
                error = notificationGlobalSettings->setMode(NotificationMode::Silent);
            }

            if (error == NotificationSettingsError::None)
            {
                QHash<QString, QVariant> values;
                values.insert("0", value);
                t2w->sendAppMessage(_uuid, values);
            }
        }
        else if (value == 2) // Find phone
        {
            Notification::clearEffectsForAll();
            Notification::deleteAllFromInbox();
            m_notify->notify();
        }
        else if (value == 5)
        {
            sendMode();
        }
    }
}

void ApplicationUI::triggerBattery(bool first)
{
    qDebug() << "triggerBattery";

    QHash<QString, QVariant> values;

    values.insert("0", batteryInfo->level());

    if (first)
    {
        values.insert("1", 1);
    }

    t2w->sendAppMessage(uuid[0], values);

    activeFrame->updatePhoneBattery(batteryInfo->level());
}

void ApplicationUI::sendMode()
{
    qDebug() << "sendMode";

    NotificationMode::Type mode = notificationGlobalSettings->mode();

    int value = 0;

    if (mode == NotificationMode::Normal)
    {
        value = 0;
    }
    else if (mode == NotificationMode::Silent)
    {
        value = 1;
    }

    QHash<QString, QVariant> values;
    values.insert("0", value);
    t2w->sendAppMessage(uuid[1], values);
}

void ApplicationUI::onBatteryLevelChanged(int level, BatteryChargingState::Type newChargingState)
{
    qDebug() << "onBatteryLevelChanged";

    triggerBattery(false);

    if (newChargingState == BatteryChargingState::Full || level == 100)
    {
        t2w->sendSms("Battery full", level + "%");
    }

    if (level <= 20)
    {
        t2w->sendSms("Battery low", level + "%");
    }
}
