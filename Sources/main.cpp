#include <iostream>

#include "Headers/CellularWorld.h"
#include "Headers/MainWindow.h"
#include "Headers/WorldWidget.h"

#include <QApplication>
#include <QTimer>

using namespace std;


// #include "main.moc"

int main(int argc, char ** argv) {
    int WIDTH = 1280, HEIGHT = 720;

    if (argc > 1)
        WIDTH = atoi(argv[1]);
    if (argc > 2)
        HEIGHT = atoi(argv[2]);
    if (argc > 3) {
        cout << "Too much params. [int WIDTH=1280][int HEIGHT=720][int PROC_OF_ALIVE_CELLS=30][int FPS=30][int SCALE=5]" << endl;
        exit(-1);
    }

    QApplication app(argc, argv);

    CellularWorld* world = new CellularWorld(HEIGHT-180, WIDTH);
    MainWindow* window = new MainWindow(world);

    window->resize(WIDTH, HEIGHT);
    window->show();

    return app.exec();
}