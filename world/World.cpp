#include "../headers/World.h"

int getRandomWithProbability(int probOfZeros) {
    int random = rand()%100;
    
    if(random < probOfZeros + 1) {
        return 0;
    }  

    return 1;
}

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

void World::createStates(int height, int width) {
    this->previousState = new bool*[height];
    this->currentState = new bool*[height];

    for(int y = 0; y < height; y++) {
        this->previousState[y] = new bool[width];
        this->currentState[y] = new bool[width];
    }
};

bool World::getNewStateOfCell(int y, int x) {
    int countOfAliveCells = this->previousState[y-1][x-1] + this->previousState[y-1][x] + this->previousState[y-1][x+1] + this->previousState[y][x-1] 
    + this->previousState[y][x+1] + this->previousState[y+1][x-1] + this->previousState[y+1][x] + this->previousState[y+1][x+1];

    return this->states[this->previousState[y][x]][countOfAliveCells];
}