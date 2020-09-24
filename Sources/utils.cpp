#include "../Headers/utils.h"
#include <cstdlib>


int getRandomWithProbability(int probOfZeros) {
    int random = rand()%100;
    
    if(random < probOfZeros + 1) {
        return 0;
    }  

    return 1;
}