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

#include "service.hpp"
#include "T2W API/Talk2WatchInterface.h"
#include "T2W API/UdpModule.h"
#include "T2W API/Serializer.h"

#include <bb/Application>
#include <bb/system/InvokeManager>
#include <bb/device/BatteryInfo>
#include <bb/device/BatteryChargingState>
#include <bb/platform/Notification>
#include <bb/platform/NotificationGlobalSettings>

#include <QTimer>

using namespace bb::system;
using namespace bb::device;
using namespace bb::platform;

Service::Service() :
        QObject(),
        m_invokeManager(new InvokeManager(this))
{
    m_invokeManager->connect(m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            this, SLOT(handleInvoke(const bb::system::InvokeRequest&)));


    uuid << "688fe407d65c4e8cae57ee7dc3c919c2" << "5dbac19332da46059990caa467bf5478";

    m_serializer = new Serializer(this);

    batteryInfo = new BatteryInfo();
    connect(batteryInfo, SIGNAL(levelChanged(int, bb::device::BatteryChargingState::Type)), this, SLOT(onBatteryLevelChanged(int, bb::device::BatteryChargingState::Type)));

    t2w = new Talk2WatchInterface(-1, this);

    connect(t2w, SIGNAL(transmissionReady()), this, SLOT(onTransmissionReady()));
    connect(t2w, SIGNAL(authSuccess()), this, SLOT(onAuthSuccess()));
    connect(t2w, SIGNAL(uuidRegistrationSuccess(QString)), this, SLOT(onUuidRegistrationSuccess(QString)));
    connect(t2w, SIGNAL(appMessageReceived(QString, QHash<QString, QVariant>)), this, SLOT(onAppMessageReceived(QString, QHash<QString, QVariant>)));

    // Create UdpModule object, open a UDP port for communicating with T2W and connect to signal
    udp = new UdpModule(this);
    udp->listenOnPort(9211); // this number should be changed to a random unused port
    connect(udp, SIGNAL(reveivedData(QString)), this, SLOT(onUdpDataReceived(QString)));

    notificationGlobalSettings = new NotificationGlobalSettings();
    connect(notificationGlobalSettings, SIGNAL(modeChanged(NotificationMode::Type)), this, SLOT(onModeChanged(NotificationMode::Type)));

    m_notify = new Notification();
    m_notify->setTitle("MyApp");
    m_notify->setBody("Where are you?");
}

void Service::handleInvoke(const bb::system::InvokeRequest & request)
{
    if (request.action().compare("com.nhatlu.MyAppService.RESET") == 0)
    {
        authorizeAppWithT2w();
    }

    if (request.action().compare("bb.action.STOP") == 0)
    {
        t2w->sendSms("Headless says goodbye!", "Headless is now shut down");
        bb::Application::instance()->quit();
    }
}

void Service::onTransmissionReady()
{
    authorizeAppWithT2w();

    QTimer::singleShot(300000, this, SLOT(onTransmissionReady()));
}

void Service::authorizeAppWithT2w()
{
    qDebug() << "authorizeAppWithT2w";

    // Default to false
    t2wProIsRunning = false;

    // T2W authorization request
    t2w->setAppValues("MyAppHL", "1.0.0", "MyApp1.0.0", "UPD", "9211", "");
    t2w->sendAppAuthorizationRequest();
}

void Service::onAuthSuccess()
{
    qDebug() << "onAuthSuccess";

    t2wProIsRunning = true;

    foreach (QString i, uuid)
    {
        t2w->registerAppMessageListener(i);
    }
}

void Service::onUdpDataReceived(QString _data)
{
    qDebug() << "HL : onUdpDataReceived in..." << _data;

    if(m_serializer->isValid(_data))
    {
        QHash<QString, QVariant> data = m_serializer->deserialize(_data);
        QString category = data.value("EVENT_CATEGORY").toString();
        QString type = data.value("EVENT_TYPE").toString();

        data.remove("EVENT_CATEGORY");
        data.remove("EVENT_TYPE");

        t2w->handleMessage(type, category, data);
    }
}

void Service::onUuidRegistrationSuccess(const QString &_uuid)
{
    qDebug() << "onUuidRegistrationSuccess!!!";

    if (_uuid == uuid[0])
    {
        triggerWatchApp(true);
    }
}

void Service::onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values)
{
    qDebug() << "onAppMessageReceived";

    int value = _values.values().at(0).toInt();

    if (_uuid == uuid[0])
    {
        triggerWatchApp(false);
    }
    else if (_uuid == uuid[1])
    {
        if (value == 0 || value == 1 || value == 2)
        {
            NotificationSettingsError::Type error = NotificationSettingsError::None;

            if(value == 0)
            {
                error = notificationGlobalSettings->setMode(NotificationMode::Normal);
            }
            else if(value == 1)
            {
                error = notificationGlobalSettings->setMode(NotificationMode::Vibrate);
            }
            else if(value == 2)
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

void Service::triggerWatchApp(bool first)
{
    if (t2wProIsRunning == true)
    {
        qDebug() << "triggerWatchApp";

        QHash<QString, QVariant> values;

        values.insert("0", batteryInfo->level());

        if (first)
        {
            values.insert("1", 1);
        }

        NotificationMode::Type mode = notificationGlobalSettings->mode();

        int value = 0;

        if (mode == NotificationMode::Normal)
        {
           value = 0;
        }
        else if (mode == NotificationMode::Vibrate)
        {
           value = 1;
        }
        else if (mode == NotificationMode::Silent)
        {
           value = 2;
        }

        values.insert("2", value);

        t2w->sendAppMessage(uuid[0], values);
    }
}

void Service::sendMode()
{
    if (t2wProIsRunning == true)
    {
        qDebug() << "sendMode";

        NotificationMode::Type mode = notificationGlobalSettings->mode();

        int value = 0;

        if (mode == NotificationMode::Normal)
        {
            value = 0;
        }
        else if (mode == NotificationMode::Vibrate)
        {
            value = 1;
        }
        else if (mode == NotificationMode::Silent)
        {
            value = 2;
        }

        QHash<QString, QVariant> values;
        values.insert("0", value);
        t2w->sendAppMessage(uuid[1], values);
    }
}

void Service::onBatteryLevelChanged(int level, BatteryChargingState::Type newChargingState)
{
    if (t2wProIsRunning == true)
    {
       qDebug() << "onBatteryLevelChanged";

       triggerWatchApp(false);

       if (newChargingState == BatteryChargingState::Full)
       {
           t2w->sendSms("Battery full", level + "%");
       }

       if (level == 20)
       {
           t2w->sendSms("Battery low", level + "%");
       }
    }
}

void Service::onModeChanged(NotificationMode::Type mode)
{
    qDebug() << "onModeChanged";
    triggerWatchApp(false);
}
