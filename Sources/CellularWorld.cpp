#include "../Headers/CellularWorld.h"
#include "../Headers/utils.h"
#include <cstdlib>
#include <time.h>


CellularWorld :: CellularWorld(int height, int width) {
    this->height = height;
    this->width = width;


    createStates(height, width);
};

void CellularWorld :: initializeState(int probability) {
    srand(time(NULL));

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            this->previousState[y][x] = getRandomWithProbability(probability);

            // this->previousState[y][x] = 0;
            // if(x == int(width/2)-1 && y == int(height/2)-1) {
            //     this->previousState[y][x] = getRandomWithProbability(probOfZeros);
            //     this->previousState[y][x] = 1;
            // }

            this->currentState[y][x] = this->previousState[y][x];
        }
    }
}

void CellularWorld :: updateState() {
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
}

void CellularWorld :: createStates(int height, int width) {
    this->previousState = new bool*[height];
    this->currentState = new bool*[height];

    for(int y = 0; y < height; y++) {
        this->previousState[y] = new bool[width];
        this->currentState[y] = new bool[width];
    }
}

bool** CellularWorld :: getCurrentState() {
    return this->currentState;
}

bool CellularWorld :: getNewStateOfCell(int y, int x) {
    int countOfAliveCells = this->previousState[y-1][x-1] + this->previousState[y-1][x] + this->previousState[y-1][x+1] + this->previousState[y][x-1] 
    + this->previousState[y][x+1] + this->previousState[y+1][x-1] + this->previousState[y+1][x] + this->previousState[y+1][x+1];

    return this->states[this->previousState[y][x]][countOfAliveCells];
}

int CellularWorld :: getWidth() {
    return this->width;
}

int CellularWorld :: getHeight() {
    return this->height;
}