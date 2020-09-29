#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QHBoxLayout>

#include "../Headers/AbstractWorld.h"
#include "../Headers/WorldWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AbstractWorld* world);

public slots:
    void createConfigDialog();

private:
    void createMenu();
    void createToolBar();
    void createActions();
    void createControls();
    void createWidgets(AbstractWorld* world);

    WorldWidget* worldWidget;
    QToolBar* toolBar;
    QVBoxLayout* mainLayout;
};


#endif