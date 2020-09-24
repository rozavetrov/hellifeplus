#include "../Headers/QWorldWidget.h"
#include "../Headers/AbstractWorld.h"

#include <QPaintEvent>
#include <QPainter>


QWorldWidget :: QWorldWidget(AbstractWorld* world) 
{
    this->world = world;
};


void QWorldWidget :: paintEvent(QPaintEvent* e) 
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

void QWorldWidget :: updateState() 
{
    this->world->updateState();
    update();
}