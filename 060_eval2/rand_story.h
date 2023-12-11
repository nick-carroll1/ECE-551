#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
struct parsed_t {
  /* Creates an array of pointers that provide a
     parsed story */
  char ** array;
  int num_items;
};

typedef struct parsed_t parsed_story;

char * readFile(char * filename);

parsed_story * parseStory(char * myStory, catarray_t * myCatArray, int do_not_repeat);

void printStory(parsed_story * myParsed_story);

catarray_t * parseCatsWords(char * filename, int do_not_repeat);

void freeCatArray(catarray_t * myCatArray);

#endif
