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

#include <QTimer>

using namespace bb::cascades;
using namespace bb::system;

ApplicationUI::ApplicationUI() :
        QObject(),
        m_translator(new QTranslator(this)),
        m_localeHandler(new LocaleHandler(this)),
        m_invokeManager(new InvokeManager(this))
{
    // prepare the localization
    if (!QObject::connect(m_localeHandler, SIGNAL(systemLanguageChanged()),
            this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }

    t2w = new Talk2WatchInterface(8484, this);
    uuid = "688fe407d65c4e8cae57ee7dc3c919c2";

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

    // Create UdpModule object, open a UDP port for communicating with T2W and connect to signal
    udp = new UdpModule(this);
    udp->listenOnPort(9712); // this number should be changed to a random unused port
    connect(udp, SIGNAL(reveivedData(QString)), this, SLOT(onUdpDataReceived(QString)));
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

    /*QHash<QString, QVariant> values;
    values.insert("4", 3);
    t2w->sendAppMessage(uuid, values);*/

    authorizeAppWithT2w();

    triggerBattery();

    //t2w->registerAppMessageListener(uuid);
}

void ApplicationUI::authorizeAppWithT2w()
{
    qDebug() << "authorizeAppWithT2w";
    QString appName = "MyApp";
    QString version = "1.0" ;
    QString uuid = "614bf1495f544c618df04ec1ef94dea2";  // Randomly generated online
    QString t2wAuthUdpPort = "9712";  // This should be set to the same value you used when initiating udpModule Object
    QString description = "Talk2Watch API";
    t2w->setAppValues(appName, version, uuid, "UDP", t2wAuthUdpPort, description);  // Aknowledge T2W of the app infos
    t2w->sendAppAuthorizationRequest();  // Send authorization request to T2W
}

void ApplicationUI::onUdpDataReceived(QString _data)
{
    qDebug() << _data;

    // This is called after T2W authorize the app
   /* if(_data=="AUTH_SUCCESS") {
        qDebug() << "Auth_Success!!!";
        return;
    }*/
}

void ApplicationUI::triggerBattery()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(5000);
}

void ApplicationUI::onTimeout()
{
    qDebug() << "onTimeout";
    QHash<QString, QVariant> values;
    values.insert("4", 3);
    t2w->sendAppMessage(uuid, values);
}
