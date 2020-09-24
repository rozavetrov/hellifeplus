#ifndef WORLD_H
#define WORLD_H

#include "../Headers/AbstractWorld.h"


class CellularWorld : public AbstractWorld 
{
public:
    CellularWorld(int height, int width);

    bool** previousState = {};
    bool** currentState = {};

    int width, height;
    bool states[2][9] = { {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0}}; // 0 -> 3, 1 -> 2, 3

    void initialize(int);
    void updateState();
    bool** getCurrentState();
    int getWidth();
    int getHeight();
        
private:
    void createStates(int height, int width);
    bool getNewStateOfCell(int y, int x);
};

#endif