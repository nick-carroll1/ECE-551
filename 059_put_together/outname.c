#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _string_t {
  size_t buffer;
  char * outputName;
};

typedef struct _string_t string_t;

const size_t buffer_increment = 8;

string_t * increase_buffer(string_t * myString) {
  myString->buffer++;
  myString->outputName =
      realloc(myString->outputName,
              buffer_increment * myString->buffer * sizeof(*myString->outputName));
  return myString;
}

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  string_t * myString = malloc(sizeof(*myString));
  myString->buffer = 1;
  myString->outputName =
      malloc(buffer_increment * myString->buffer * sizeof(*myString->outputName));
  size_t char_num = 0;
  while (inputName[char_num] != '\0') {
    if (char_num % buffer_increment == 0) {
      myString = increase_buffer(myString);
    }
    myString->outputName[char_num] = inputName[char_num];
    char_num++;
  }
  if (char_num % buffer_increment != 0) {
    myString = increase_buffer(myString);
  }
  for (size_t i = 0; i < buffer_increment; i++) {
    switch (i) {
      case 0:
        myString->outputName[char_num] = '.';
        break;
      case 1:
        myString->outputName[char_num] = 'c';
        break;
      case 2:
        myString->outputName[char_num] = 'o';
        break;
      case 3:
        myString->outputName[char_num] = 'u';
        break;
      case 4:
        myString->outputName[char_num] = 'n';
        break;
      case 5:
        myString->outputName[char_num] = 't';
        break;
      case 6:
        myString->outputName[char_num] = 's';
        break;
      case 7:
        myString->outputName[char_num] = '\0';
        break;
    }
    char_num++;
  }
  char * temp = myString->outputName;
  free(myString);
  return temp;
}
