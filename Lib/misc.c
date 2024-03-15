#include <stdlib.h>

int GetRandom (int iLow, int iHighEx){
    return iLow + (rand() % (iHighEx - iLow));
}