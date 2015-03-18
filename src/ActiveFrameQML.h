/*
 * ActiveFrame.h
 *
 *  Created on: Apr 2, 2013
 *      Author: wbarichak
 */

#ifndef ACTIVEFRAMEQML_H_
#define ACTIVEFRAMEQML_H_

#include <QObject>
#include <bb/cascades/Label>
#include <bb/cascades/SceneCover>

using namespace ::bb::cascades;

class ActiveFrameQML: public SceneCover {
    Q_OBJECT

public:
    ActiveFrameQML(QObject *parent=0);

    Q_INVOKABLE void updatePebbleBattery(int level);
    Q_INVOKABLE void updatePhoneBattery(int level);

public slots:


private:
    bb::cascades::Label *m_PebbleBatteryLabel;
    bb::cascades::Label *m_PhoneBatteryLabel;
};

#endif /* ACTIVEFRAMEQML_H_ */
