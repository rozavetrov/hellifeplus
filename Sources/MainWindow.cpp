#include "../Headers/MainWindow.h"
#include "../Headers/AbstractWorld.h"
#include "../Headers/QWorldWidget.h"

#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>


MainWindow :: MainWindow(AbstractWorld* world)
{
    createMenu();
    createToolBar();
    createWidgets(world);

    
}


void MainWindow :: createMenu()
{
    QMenu* menu = menuBar()->addMenu(tr("File"));
    menu->addAction(tr("Quit"), this, &QWidget::close);
}

void MainWindow :: createToolBar()
{
    QToolBar* tb = new QToolBar("Instruments", this);
    addToolBar(tb);
}

void MainWindow :: createWidgets(AbstractWorld* world)
{
    QWidget *centralWidget = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    this->worldWidget = new QWorldWidget(world);
    mainLayout->addWidget(this->worldWidget);
}