#ifndef WORLD_H
#define WORLD_H
#include <QWidget>


class World : public QWidget {
    Q_OBJECT

    public: 
        bool** previousState = {};
        bool** currentState = {};

        bool states[2][9] = { {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0}}; // 0 -> 3, 1 -> 2, 3
        int width, height;

        void initialize(int);
       
        World(int height, int width);
        
    public slots:
        void createNewState();

    signals:
        void stateChanged(bool** newState);

    private:
        void createStates(int height, int width);

        bool getNewStateOfCell(int y, int x);
};

#endif