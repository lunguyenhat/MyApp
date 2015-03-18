#include "ActiveFrameQML.h"

#include <bb/cascades/SceneCover>
#include <bb/cascades/Container>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>

using namespace bb::cascades;

ActiveFrameQML::ActiveFrameQML(QObject *parent)
    : SceneCover(parent)
{
    QmlDocument *qml = QmlDocument::create("asset:///AppCover.qml")
            .parent(parent);
    Container *mainContainer = qml->createRootObject<Container>();
    setContent(mainContainer);

    m_PebbleBatteryLabel = mainContainer->findChild<Label*>("PebbleBattery");
    m_PebbleBatteryLabel->setParent(mainContainer);

    m_PhoneBatteryLabel = mainContainer->findChild<Label*>("PhoneBattery");
    m_PhoneBatteryLabel->setParent(mainContainer);
}

void ActiveFrameQML::updatePebbleBattery(int level)
{
    char battery_phone_buffer[20];
    snprintf(battery_phone_buffer, sizeof(battery_phone_buffer), "Pebble Battery: %d%%", level);
    m_PebbleBatteryLabel->setText(battery_phone_buffer);
}

void ActiveFrameQML::updatePhoneBattery(int level)
{
    char battery_phone_buffer[20];
    snprintf(battery_phone_buffer, sizeof(battery_phone_buffer), "Phone Battery: %d%%", level);
    m_PhoneBatteryLabel->setText(battery_phone_buffer);
}
