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

// works
int ToDigitVal(char digit) {
  char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  int i = 0;
  for (i = 0; i < 16; i++) {
    if (digit == hexDigits[i]) {
      return i;
    }

    if (digit == hexDigits[i]+32) {
      return i;
    }
  }
  return 0;
}

// kinda tested
int Power(int number, int exponent) {
  int i = 0;
  int answer = 1;
  for (i = 0; i < exponent; i++) {
      answer *= number;
  }
  return answer;
}


unsigned int HexArrayToUInt16(char *pArray) {
  // max value for array is 4 elements.
  int pArrayLen = 4;
  int i = 0;
  unsigned int myBinaryValue;
  for (i = 0; i < pArrayLen; i++) {
    myBinaryValue += ToDigitVal(*(pArray + pArrayLen - i - 1)) * Power(16, i);
  }
  return myBinaryValue;
}
