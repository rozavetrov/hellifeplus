#include "../Headers/MainWindow.h"
#include "../Headers/AbstractWorld.h"
#include "../Headers/WorldWidget.h"
#include "../Headers/ConfigDialog.h"

#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>
#include <QAction>
#include <QSlider>


MainWindow :: MainWindow(AbstractWorld* world)
{
    this->createMenu();
    this->createToolBar();
    this->createWidgets(world);
    this->createActions();
    this->createConfigDialog();

    this->worldWidget->restart(98);
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
    QWidget* centralWidget = new QWidget(this);

    this->mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    this->worldWidget = new WorldWidget(world);
    mainLayout->addWidget(this->worldWidget);

    setCentralWidget(centralWidget);
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

    const QIcon restartIcon = QIcon("./Resources/ButtonIcons/restart.png");
    QAction *restartAction = new QAction(restartIcon, tr("&Stop"), this);

    QObject::connect(restartAction, &QAction::triggered, this, &MainWindow::createConfigDialog);
    this->toolBar->addAction(restartAction);
}

void MainWindow :: createConfigDialog()
{
    ConfigDialog* dialog = new ConfigDialog();
    
    if(dialog->exec()) {
        int probability = dialog->getProbabilityOfDeadCells();
        this->worldWidget->restart(100 - probability);
    }

    delete dialog;
}