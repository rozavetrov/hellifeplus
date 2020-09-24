#ifndef QWORLD_WIDGET_H
#define QWORLD_WIDGET_H

#include "../Headers/AbstractWorld.h"

#include <QTimer>
#include <QWidget>
#include <QPaintEvent>


class WorldWidget : public QWidget 
{
    Q_OBJECT

public:
    WorldWidget(AbstractWorld* world);
    void paintEvent(QPaintEvent* e);

public slots:
    void resume();
    void stop();
    void pause();

private:
    AbstractWorld* world;
    QTimer timer;
    int scale = 1;

    void connectSignals();
};

#endif