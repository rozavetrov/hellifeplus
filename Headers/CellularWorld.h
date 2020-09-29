#ifndef WORLD_H
#define WORLD_H

#include "../Headers/AbstractWorld.h"


// Realization of "AbstractWorld" interface
class CellularWorld : public AbstractWorld 
{
public:
    CellularWorld(int height, int width);

    bool** previousState = {};
    bool** currentState = {};

    bool rule[2][9] = { {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}; // 0 -> 3, 1 -> 2, 3

    void initializeState(int);
    void updateState();
    bool** getCurrentState();
    void setRule(bool** newRule);

    int getWidth();
    int getHeight();
        
private:
    int width, height;

    void createStates(int height, int width);
    bool getNewStateOfCell(int y, int x);
};

#endif