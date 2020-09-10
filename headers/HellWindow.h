#ifndef HELLWINDOW_H
#define HELLWINDOW_H

#include <QWidget>
#include <QPaintEvent>


class HellWindow : public QWidget {
    Q_OBJECT

    public:
        void initialize(bool** state);

        HellWindow(int width, int height, int scale);
        virtual void paintEvent(QPaintEvent * e);

        int width, height;

    public slots:
        void updateState(bool** newState);

    private:
        int scale;
        bool** currentState = {};
};

#endif