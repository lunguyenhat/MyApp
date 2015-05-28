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

#include <bb/Application>
#include <bb/system/InvokeManager>
#include <bb/device/BatteryInfo>
#include <bb/device/BatteryChargingState>
#include <bb/platform/Notification>
#include <bb/platform/NotificationGlobalSettings>
#include <bb/platform/NotificationMode>

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

    batteryInfo = new BatteryInfo();
    connect(batteryInfo, SIGNAL(levelChanged(int, bb::device::BatteryChargingState::Type)), this, SLOT(onBatteryLevelChanged(int, bb::device::BatteryChargingState::Type)));

    t2w = new Talk2WatchInterface(8484, this);

    connect(t2w, SIGNAL(transmissionReady()), this, SLOT(onTransmissionReady()));
    connect(t2w, SIGNAL(authSuccess()), this, SLOT(onAuthSuccess()));
    connect(t2w, SIGNAL(uuidRegistrationSuccess(QString)), this, SLOT(onUuidRegistrationSuccess(QString)));
    connect(t2w, SIGNAL(appMessageReceived(QString, QHash<QString, QVariant>)), this, SLOT(onAppMessageReceived(QString, QHash<QString, QVariant>)));

    // Create UdpModule object, open a UDP port for communicating with T2W and connect to signal
    udp = new UdpModule(this);
    udp->listenOnPort(9211); // this number should be changed to a random unused port
    //connect(udp, SIGNAL(reveivedData(QString)), this, SLOT(onUdpDataReceived(QString)));

    notificationGlobalSettings = new NotificationGlobalSettings();
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
    // Checks every minute to make sure T2W is still running
    authorizeAppWithT2w();

    QTimer::singleShot(60000, this, SLOT(onTransmissionReady()));
}

void Service::authorizeAppWithT2w()
{
    // Default to false
    t2wProIsRunning = false;

    // T2W authorization request
    t2w->setAppValues("MyApp", "1.0.0", "MyApp1.0.0", "UPD", "9211", "");
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

    if (_data == "AUTH_SUCCESS")
    {
        onAuthSuccess();
    }

    /*if(_category=="PEBBLE")
     {
         if(_type=="APPMESSAGE_RECEIVED")
         {
             QHash<QString, QVariant> values = _values;
             QString uuid = _values.value("uuid").toString();
             values.remove("uuid");

             onAppMessageReceived(uuid, values);
         }
         else if(_type=="APP_STARTED")
         {}
         else if(_type=="APP_CLOSED")
         {}
     }
     else if(_category=="PEBBLE_NOTIFICATIONS")
     {
         qDebug() << "__EVENT__" << _type; //<< _values;

         QString id = _values.value("id").toString();
         QString text = _values.value("text").toString();

         if(_type=="DISMISS")
         {}
         else if(_type=="GENERIC")
         {}
         else if(_type=="RESPONSE")
         {}

     }
     else if(_category=="APP_CONNECTION")
     {
         qDebug() << "__RX__" << _type << _values;

         QString action = _values.value("action").toString();
         QString error = _values.value("error").toString();
         QString folder = _values.value("folder").toString();
         QString uuid = _values.value("uuid").toString();

         if(_type=="AUTH_SUCCESS")
         {
             onAuthSuccess();
         }
         else if(_type=="AUTH_ERROR")
         {}
         else if(_type=="CREATE_ACTION_SUCCESS")
         {}
         else if(_type=="CREATE_ACTION_ERROR")
         {}
         else if(_type=="REMOVE_ACTION_SUCCESS")
         {}
         else if(_type=="REMOVE_ACTION_ERROR")
         {}
         else if(_type=="RENAME_ACTION_SUCCESS")
         {}
         else if(_type=="RENAME_ACTION_ERROR")
         {}
         else if(_type=="ACTION_TRIGGERED")
         {}
         else if(_type=="REMOVE_CONNECTION_SUCCESS")
         {}
         else if(_type=="CREATE_FOLDER_SUCCESS")
         {}
         else if(_type=="CREATE_FOLDER_ERROR")
         {}
         else if(_type=="REMOVE_FOLDER_SUCCESS")
         {}
         else if(_type=="REMOVE_FOLDER_ERROR")
         {}
         else if(_type=="RENAME_FOLDER_SUCCESS")
         {}
         else if(_type=="RENAME_FOLDER_ERROR")
         {}
         else if(_type=="REGISTER_UUID_SUCCESS")
             onUuidRegistrationSuccess(uuid);
         else if(_type=="DEREGISTER_UUID_SUCCESS")
         {}
     }*/
}

void Service::onUuidRegistrationSuccess(const QString &_uuid)
{
    qDebug() << "onUuidRegistrationSuccess!!!";

    if (_uuid == uuid[0])
    {
        triggerBattery(true);
    }
}

void Service::onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values)
{
    qDebug() << "onAppMessageReceived";

    int value = _values.values().at(0).toInt();

    if (_uuid == uuid[0])
    {
        triggerBattery(false);
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

void Service::triggerBattery(bool first)
{
    if (t2wProIsRunning == true)
    {
        qDebug() << "triggerBattery";

        QHash<QString, QVariant> values;

        values.insert("0", batteryInfo->level());

        if (first)
        {
            values.insert("1", 1);
        }

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
        else if (mode == NotificationMode::Silent)
        {
            value = 1;
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
}
