#ifndef QWORLD_WIDGET_H
#define QWORLD_WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "../Headers/AbstractWorld.h"


class QWorldWidget : public QWidget 
{
    Q_OBJECT

public:
    QWorldWidget(AbstractWorld* world);
    void paintEvent(QPaintEvent* e);

public slots:
    void updateState();

private:
    AbstractWorld* world;
    int scale=1;
};

#endif