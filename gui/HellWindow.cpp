#include "../headers/HellWindow.h"
#include <QPaintEvent>
#include <QPainter>


HellWindow :: HellWindow(int width, int height, int scale) {
    this->scale = scale;
    this->width = width;
    this->height = height;
};

void HellWindow::initialize(bool** state) {
    this->currentState = state;
}

void HellWindow :: paintEvent(QPaintEvent * e) {
    QPainter painter(this);

    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
            if (this->currentState[y][x]) {
                QRect r(x*this->scale, y*this->scale, this->scale, this->scale);
                painter.fillRect(r, Qt::darkGreen);
        }
}

void HellWindow :: updateState(bool** currentState) {
    this->currentState = currentState;
    update();
}