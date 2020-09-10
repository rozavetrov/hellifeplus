#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include <QWidget>
#include <QTimer>


using namespace std;

int getRandomWithProbability(int probOfZeros) {
    int random = rand()%100;
    
    if(random < probOfZeros + 1) {
        return 0;
    }  

    return 1;
}


class World {
    public: 
        bool*** map = {};
        int states[2][9] = { {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0}}; // 0 -> 3, 1 -> 2, 3
        int time, width, height;

        void initialize(int);
        void create();

        World(int, int, int);
        
        friend ostream& operator<< (ostream&, World&);
    private:
        void createMap(int time, int height, int width) {
            this->map = new bool**[time];
            for(int t = 0; t < time; t++) {
                this->map[t] = new bool*[height];
                
                for (int i = 0; i < height; i++) {
                    this->map[t][i] = new bool[width];
                }
            }
        }

        int getNewStateOfCell(int t, int y, int x) {
            int countOfAliveCells = this->map[t][y-1][x-1] + this->map[t][y-1][x] + this->map[t][y-1][x+1] + this->map[t][y][x-1] + this->map[t][y][x+1]
            + this->map[t][y+1][x-1] + this->map[t][y+1][x] + this->map[t][y+1][x+1];

            return this->states[this->map[t][y][x]][countOfAliveCells];
        }
};

World::World(int time, int height, int width) {
    this->time = time;
    this->height = height;
    this->width = width;


    createMap(time, height, width);
};

void World::initialize(int probOfZeros) {
    for(int i=0; i < height; i++) {
        for(int j=0; j < width; j++) {
            this->map[0][i][j] = getRandomWithProbability(probOfZeros);
        }
    }
}

void World::create() {
    for(int t=1; t < this->time; t++) {
        for(int i=1; i < this->height-1; i++) {
            for(int j=1; j < this->width-1; j++) {
                this->map[t][i][j] = this->getNewStateOfCell(t-1, i, j);
            }
        }
    }
}

ostream& operator << (ostream &out, World &world) {
    for (int t = 0; t < world.time; t++) {
        for (int i = 0; i < world.height; i++) {
            for (int j = 0; j < world.width; j++) {
                out << world.map[t][i][j] << " ";
            }
            out << endl;
        }
        out << endl << endl;
    }

    return out;
}


class DemoObj : public QWidget {
Q_OBJECT

public:
    World* world;

    DemoObj(int time, int width, int height, int procOfAliveCells, int delay, int scale);
    virtual void paintEvent(QPaintEvent * e);

public slots:
   void AdvanceState();

private:
    int scale;
    int currentTime = 0;
    bool** currentState;
    
    QTimer _timer;
};

DemoObj :: DemoObj(int time, int width, int height, int procOfAliveCells, int fps, int scale) {
    this->scale = scale;

    this->world = new World(time, int(height/scale), int(width/scale));
    this->world->initialize(100 - procOfAliveCells);
    this->world->create();

    connect(&_timer, SIGNAL(timeout()), this, SLOT(AdvanceState()));
    _timer.start(int(1000/fps));   // delay per frame.
};


void DemoObj :: paintEvent(QPaintEvent * e) {
    QPainter painter(this);

    for (int y = 0; y < this->world->height; y++)
        for (int x = 0; x < this->world->width; x++) {
            if (this->world->map[this->currentTime][y][x]) {
                QRect r(x*this->scale, y*this->scale, this->scale, this->scale);
                painter.fillRect(r, Qt::darkGreen);
            }
        }
}

void DemoObj :: AdvanceState() {
    // cout << this->currentTime << endl;
    if (this->currentTime < this->world->time) {
        this->currentTime++;
        this->currentState = this->world->map[this->currentTime - 1];
        update();
    }
}

#include "main.moc"

int main(int argc, char ** argv) {
    srand(time(NULL));

    int WIDTH = 1280, HEIGHT = 720, FPS = 30, SCALE = 5;
    int PROC_OF_ALIVE_CELLS = 30;

    if (argc < 2) {
        cout << "Requirement param 'TIME' is undefined. [int TIME(REQUIRED)][int WIDTH=1280][int HEIGHT=720][int PROC_OF_ALIVE_CELLS=30][int FPS=30][int SCALE=5]" << endl;
        exit(-1);
    }
    if (argc > 2)
        WIDTH = atoi(argv[2]);
    if (argc > 3)
        HEIGHT = atoi(argv[3]);
    if (argc > 4)
        PROC_OF_ALIVE_CELLS = atoi(argv[4]);
    if (argc > 5)
        FPS = atoi(argv[5]);
    if (argc > 6)
        SCALE = atoi(argv[6]);
    if (argc > 7) {
        cout << "Too much params. [int TIME(REQUIRED)][int WIDTH=1280][int HEIGHT=720][int PROC_OF_ALIVE_CELLS=30][int FPS=30][int SCALE=5]" << endl;
        exit(-1);
    }
    
    int TIME = atoi(argv[1]);

    QApplication app(argc, argv);

    cout << "TIME: " << TIME << endl;
    cout << "RESOLUTION: " << WIDTH << "x" << HEIGHT << endl;
    cout << "FPS: " << FPS << endl;

    DemoObj *obj = new DemoObj(TIME, WIDTH, HEIGHT, PROC_OF_ALIVE_CELLS, FPS, SCALE);

    obj->resize(WIDTH, HEIGHT);
    obj->show();

    return app.exec();
}