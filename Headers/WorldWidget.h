#ifndef QWORLD_WIDGET_H
#define QWORLD_WIDGET_H

#include "../Headers/AbstractWorld.h"

#include <QTimer>
#include <QWidget>
#include <QPaintEvent>


// Main widget to paint world
class WorldWidget : public QWidget 
{
    Q_OBJECT

public:
    WorldWidget(AbstractWorld* world);
    void paintEvent(QPaintEvent* e);
    void setRule(bool**);

public slots:
    void resume();
    void restart(int probability);
    void pause();

private:
    AbstractWorld* world;
    QTimer timer;
    int scale = 1;

    void connectSignals();
};

#endif