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

#include "T2W API/Talk2WatchInterface.h"
#include "T2W API/UdpModule.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/system/InvokeManager>
#include <bb/device/BatteryInfo>
#include <bb/device/BatteryChargingState>
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
    //uuid[0] = "688fe407d65c4e8cae57ee7dc3c919c2";
    //uuid[1] = "5dbac19332da46059990caa467bf5478";

    uuid << "688fe407d65c4e8cae57ee7dc3c919c2" << "5dbac19332da46059990caa467bf5478";

    batteryInfo = new BatteryInfo();
    qDebug() << connect(batteryInfo, SIGNAL(levelChanged(int, bb::device::BatteryChargingState::Type)), this, SLOT(onBatteryLevelChanged(int, bb::device::BatteryChargingState::Type)));

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Make app available to the qml.
    qml->setContextProperty("app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    connect(t2w, SIGNAL(transmissionReady()), this, SLOT(onTransmissionReady()));
    connect(t2w, SIGNAL(authSuccess()), this, SLOT(onAuthSuccess()));
    connect(t2w, SIGNAL(uuidRegistrationSuccess(QString)), this, SLOT(onUuidRegistrationSuccess(QString)));
    connect(t2w, SIGNAL(appMessageReceived(QString, QHash<QString, QVariant>)), this, SLOT(onAppMessageReceived(QString, QHash<QString, QVariant>)));

    // Create UdpModule object, open a UDP port for communicating with T2W and connect to signal
    udp = new UdpModule(this);
    udp->listenOnPort(9712); // this number should be changed to a random unused port

    notificationGlobalSettings = new NotificationGlobalSettings();

    connect(myapp, SIGNAL(manualExit()), this, SLOT(onManualExit()));
    myapp->setAutoExit(false);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_translator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("MyApp_%1").arg(locale_string);
    if (m_translator->load(file_name, "app/native/qm")) {
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

void ApplicationUI::resendNotification()
{
    InvokeRequest request;
    request.setTarget("com.example.MyAppService");
    request.setAction("com.example.MyAppService.RESET");
    m_invokeManager->invoke(request);
    Application::instance()->minimize();
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
        triggerBattery();
    }
}

void ApplicationUI::onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values)
{
    qDebug() << "onAppMessageReceived";

    if (_uuid == uuid[0])
    {
        triggerBattery();
    }
    else if (_uuid == uuid[1])
    {
        int value = _values.values().at(0).toInt();

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
        else if (value == 5)
        {
            sendMode();
        }
    }
}

void ApplicationUI::triggerBattery()
{
    qDebug() << "triggerBattery";

    QHash<QString, QVariant> values;
    values.insert("4", batteryInfo->level());
    t2w->sendAppMessage(uuid[0], values);
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

    QHash<QString, QVariant> values;
    values.insert("4", level);
    t2w->sendAppMessage(uuid[0], values);
}
