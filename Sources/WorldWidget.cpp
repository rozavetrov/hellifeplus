#include "../Headers/AbstractWorld.h"
#include "../Headers/WorldWidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QObject>


WorldWidget :: WorldWidget(AbstractWorld* world) 
{
    this->world = world;
    this->connectSignals();
};


void WorldWidget :: paintEvent(QPaintEvent* e) 
{
    QPainter painter(this);

    for (int y = 0; y < this->world->getHeight(); y++)
        for (int x = 0; x < this->world->getWidth(); x++) {
            if (this->world->getCurrentState()[y][x]) {
                QRect r(x*this->scale, y*this->scale, this->scale, this->scale);
                painter.fillRect(r, Qt::darkGreen);
            }
        }
}

void WorldWidget :: resume() 
{
    timer.start(int(1000/60));

    this->world->updateState();
    update();
}

void WorldWidget :: stop()
{
    this->timer.stop();
    this->world->initializeState(95);
    update();
}

void WorldWidget :: pause()
{
    this->timer.stop();
}


void WorldWidget :: connectSignals()
{
    QObject::connect(&this->timer, &QTimer::timeout, this, &WorldWidget::resume);
}