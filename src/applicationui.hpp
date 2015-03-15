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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QStringList>
#include <bb/device/BatteryChargingState>

class Talk2WatchInterface;
class UdpModule;

namespace bb {
    namespace cascades {
        class Application;
        class LocaleHandler;
    }
    namespace system {
        class InvokeManager;
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

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI: public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }

    Q_INVOKABLE void resendNotification();

private slots:
    void onSystemLanguageChanged();
    void onManualExit();

    void onTransmissionReady();
    void onAuthSuccess();
    void onUuidRegistrationSuccess(const QString &_uuid);
    void onAppMessageReceived(const QString &_uuid, const QHash<QString, QVariant> &_values);

    void onBatteryLevelChanged(int level, bb::device::BatteryChargingState::Type newChargingState);

private:

    Talk2WatchInterface* t2w;
    UdpModule *udp;

    QStringList uuid;

    bb::device::BatteryInfo* batteryInfo;
    bb::platform::NotificationGlobalSettings* notificationGlobalSettings;

    void authorizeAppWithT2w();
    void triggerBattery();
    void sendMode();

    bb::platform::Notification * m_notify;

    QTranslator* m_translator;
    bb::cascades::LocaleHandler* m_localeHandler;
    bb::system::InvokeManager* m_invokeManager;
    bb::cascades::Application * myapp;
};

#endif /* ApplicationUI_HPP_ */
