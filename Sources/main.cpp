#include <iostream>

#include "Headers/QWorldWidget.h"
#include "Headers/CellularWorld.h"
#include "Headers/MainWindow.h"
#include "./Headers/QWorldWidget.h"

#include <QApplication>
#include <QTimer>


using namespace std;


// #include "main.moc"

int main(int argc, char ** argv) {
    srand(time(NULL));

    int WIDTH = 1280, HEIGHT = 720, FPS = 30, SCALE = 5;
    int PROC_OF_ALIVE_CELLS = 30;

    if (argc > 1)
        WIDTH = atoi(argv[1]);
    if (argc > 2)
        HEIGHT = atoi(argv[2]);
    if (argc > 3)
        PROC_OF_ALIVE_CELLS = atoi(argv[3]);
    if (argc > 4)
        FPS = atoi(argv[4]);
    if (argc > 5)
        SCALE = atoi(argv[5]);
    if (argc > 6) {
        cout << "Too much params. [int WIDTH=1280][int HEIGHT=720][int PROC_OF_ALIVE_CELLS=30][int FPS=30][int SCALE=5]" << endl;
        exit(-1);
    }
    
    QApplication app(argc, argv);

    CellularWorld* world = new CellularWorld(HEIGHT, WIDTH);
    world->initialize(100-PROC_OF_ALIVE_CELLS);
        
    MainWindow* window = new MainWindow(world);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, window->worldWidget, &QWorldWidget::updateState);
    timer.start(int(1000/60));
    

    window->resize(WIDTH, HEIGHT);
    window->show();

    return app.exec();
}