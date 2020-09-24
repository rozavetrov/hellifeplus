#include "../Headers/MainWindow.h"
#include "../Headers/AbstractWorld.h"
#include "../Headers/WorldWidget.h"

#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>
#include <QAction>


MainWindow :: MainWindow(AbstractWorld* world)
{
    createMenu();
    createToolBar();
    createWidgets(world);
    createActions();

    this->worldWidget->stop();
}


void MainWindow :: createMenu()
{
    QMenu* menu = menuBar()->addMenu(tr("File"));
    menu->addAction(tr("Quit"), this, &QWidget::close);
}

void MainWindow :: createToolBar()
{
    toolBar = new QToolBar("&Instruments", this);
    addToolBar(toolBar);
}

void MainWindow :: createWidgets(AbstractWorld* world)
{
    QWidget *centralWidget = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    this->worldWidget = new WorldWidget(world);
    mainLayout->addWidget(this->worldWidget);
}

void MainWindow :: createActions()
{   
    const QIcon pauseIcon = QIcon("./Resources/ButtonIcons/pause.png");
    QAction *pauseAction = new QAction(pauseIcon, tr("&Pause"), this);

    QObject::connect(pauseAction, &QAction::triggered, this->worldWidget, &WorldWidget::pause);
    this->toolBar->addAction(pauseAction);

    const QIcon playIcon = QIcon("./Resources/ButtonIcons/play.png");
    QAction *playAction = new QAction(playIcon, tr("&Play"), this);

    QObject::connect(playAction, &QAction::triggered, this->worldWidget, &WorldWidget::resume);
    this->toolBar->addAction(playAction);

    const QIcon stopIcon = QIcon("./Resources/ButtonIcons/stop.png");
    QAction *stopAction = new QAction(stopIcon, tr("&Stop"), this);

    QObject::connect(stopAction, &QAction::triggered, this->worldWidget, &WorldWidget::stop);
    this->toolBar->addAction(stopAction);
}