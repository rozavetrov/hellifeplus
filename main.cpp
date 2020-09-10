#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QObject>


using namespace std;

int getRandomWithProbability(int probOfZeros) {
    int random = rand()%100;
    
    if(random < probOfZeros + 1) {
        return 0;
    }  

    return 1;
}


class World : public QWidget {
    Q_OBJECT

    public: 
        bool** previousState = {};
        bool** currentState = {};

        bool states[2][9] = { {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0}}; // 0 -> 3, 1 -> 2, 3
        int width, height;

        void initialize(int);
       
        World(int height, int width);
        
        friend ostream& operator<< (ostream&, World&);
    
    public slots:
         void createNewState();

    signals:
        void stateChanged(bool** newState);

    private:
        void createStates(int height, int width) {
            this->previousState = new bool*[height];
            this->currentState = new bool*[height];

            for(int y = 0; y < height; y++) {
                this->previousState[y] = new bool[width];
                this->currentState[y] = new bool[width];
            }
        }

        bool getNewStateOfCell(int y, int x) {
            int countOfAliveCells = this->previousState[y-1][x-1] + this->previousState[y-1][x] + this->previousState[y-1][x+1] + this->previousState[y][x-1] 
            + this->previousState[y][x+1] + this->previousState[y+1][x-1] + this->previousState[y+1][x] + this->previousState[y+1][x+1];

            // int countOfAliveCells = this->previousState[y-1][x] + this->previousState[y][x-1] 
            // + this->previousState[y][x+1] + this->previousState[y+1][x];

            return this->states[this->previousState[y][x]][countOfAliveCells];
        }
};

World::World(int height, int width) {
    this->height = height;
    this->width = width;


    createStates(height, width);
};

void World::initialize(int probOfZeros) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            this->previousState[y][x] = getRandomWithProbability(probOfZeros);
            this->currentState[y][x] = this->previousState[y][x];
        }
    }
}

void World::createNewState() {
    for(int y = 1; y < this->height - 1; y++) {
        for(int x = 1; x < this->width - 1; x++) {
            this->currentState[y][x] = this->getNewStateOfCell(y, x);
        }
    }
    for(int y = 1; y < this->height - 1; y++) {
        for(int x = 1; x < this->width - 1; x++) {
            this->previousState[y][x] = this->currentState[y][x];
        }
    }

    emit stateChanged(this->currentState);
}


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

#include "main.moc"

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

    cout << "RESOLUTION: " << WIDTH << "x" << HEIGHT << endl;
    cout << "FPS: " << FPS << endl;

    HellWindow *window = new HellWindow(WIDTH, HEIGHT, SCALE);
    World *world = new World(HEIGHT, WIDTH);

    world->initialize(100 - PROC_OF_ALIVE_CELLS);
    window->initialize(world->currentState);

    QObject::connect(world, &World::stateChanged, window, &HellWindow::updateState);
    
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, world, &World::createNewState);

    timer.start(int(1000/FPS));

    window->resize(WIDTH, HEIGHT);
    window->show();

    return app.exec();
}