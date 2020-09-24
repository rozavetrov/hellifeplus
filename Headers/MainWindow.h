#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "../Headers/AbstractWorld.h"
#include "../Headers/QWorldWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AbstractWorld* world);
    QWorldWidget* worldWidget;

private:
    void createMenu();
    void createToolBar();
    void createWidgets(AbstractWorld* world);
};


#endif