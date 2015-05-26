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

#ifndef SERVICE_H_
#define SERVICE_H_

#include <QObject>
#include <QStringList>
#include <bb/device/BatteryChargingState>

namespace bb {
    class Application;

    namespace system {
        class InvokeManager;
        class InvokeRequest;
    }

    namespace device {
        class BatteryInfo;
        class BatteryChargingState;
    }

    namespace platform {
        class NotificationGlobalSettings;
        class Notification;
    }
}

class Talk2WatchInterface;
class UdpModule;

class Service: public QObject
{
    Q_OBJECT
public:
    Service();
    virtual ~Service() {}
private slots:
    void handleInvoke(const bb::system::InvokeRequest &);

    void onTransmissionReady();
    /*void onAuthSuccess();
    void onUuidRegistrationSuccess(const QString &_uuid);
    void onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values);*/

    void onBatteryLevelChanged(int level, bb::device::BatteryChargingState::Type newChargingState);

    void onUdpDataReceived(QString _data);

private:
    bb::system::InvokeManager * m_invokeManager;

    void authorizeAppWithT2w();
    void triggerBattery(bool first);
    void sendMode();

    Talk2WatchInterface* t2w;
    UdpModule* udp;

    QStringList uuid;

    bb::platform::Notification * m_notify;

    bb::device::BatteryInfo* batteryInfo;
    bb::platform::NotificationGlobalSettings* notificationGlobalSettings;

    bool t2wProIsRunning;
};

#endif /* SERVICE_H_ */
