#include <stdlib.h>
#include "misc.h"

unsigned char vowels[10] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};

int GetRandom (int iLow, int iHighEx){
    return iLow + (rand() % (iHighEx - iLow));
}

int isVowel(unsigned char pData) {
  // a, e, i, o, u
  int i;
  for (i = 0; i < 10; i++){
    if (vowels[i] == pData) return 1;
  }
  return 0;
}