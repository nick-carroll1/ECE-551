#include "rand_story.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void check_file_isNot_empty(char * filename) {
  /* Reads the first character of a file and confirms it isn't empty
   */
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "There was an error opening the file.\n");
    exit(EXIT_FAILURE);
  }
  if (fgetc(f) == EOF) {
    fclose(f);
    exit(EXIT_SUCCESS);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "There was an error closing the file.\n");
    exit(EXIT_FAILURE);
  }
}

char * readFile(char * filename) {
  /* Reads the story template.
   */
  check_file_isNot_empty(filename);
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "There was an error opening the file.\n");
    exit(EXIT_FAILURE);
  }
  char * myStory = NULL;
  size_t linecap = 0;
  // Using getdelim as read from man pages instead of getline because there does not seem to be a benefit for separating each line
  getdelim(&myStory, &linecap, '\0', f);
  if (myStory == NULL) {
    fprintf(stderr, "There was an error reading the file.\n");
    exit(EXIT_FAILURE);
  }
  // error checking with errno per man page
  if (errno == EINVAL || errno == ENOMEM) {
    fprintf(stderr, "There was an error reading the file.\n");
    free(myStory);
    exit(EXIT_FAILURE);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "There was an error closing the file.\n");
    free(myStory);
    exit(EXIT_FAILURE);
  }
  return myStory;
}

int check_positive_int(char * category) {
  /* Check if the category in the stroy is a positive integer
     return the positive if it is, otherwise return 0
  */
  int eachChar = 0;
  // Look through each character and ensure they are all numerical
  while (category[eachChar] != '_' && category[eachChar] != '\0') {
    if (category[eachChar] < '0' || category[eachChar] > '9') {
      return 0;
    }
    eachChar++;
  }
  return atoi(category);
}

void free_parsed_story(parsed_story * myParsed_story) {
  /* Frees the memory associated with a parsed_story
   */
  free(myParsed_story->array);
  free(myParsed_story);
}

void freeCatArray(catarray_t * myCatArray) {
  /* Frees all of the memory in a category array
     First frees all of the words in memory
     Then frees the remainder of the category
  */
  for (size_t eachCat = 0; eachCat < myCatArray->n; eachCat++) {
    for (size_t eachWord = 0; eachWord < myCatArray->arr[eachCat].n_words; eachWord++) {
      free(myCatArray->arr[eachCat].words[eachWord]);
    }
    free(myCatArray->arr[eachCat].words);
    free(myCatArray->arr[eachCat].name);
  }
  free(myCatArray->arr);
  free(myCatArray);
}

int findCategory(char * blank,
                 parsed_story * myParsed_story,
                 parsed_story * usedWords,
                 char * myStory) {
  /* Searches ahead in the story template to find the Category
   */
  int eachChar = 0;
  // Look through each character searching for the next underscore
  while (blank[eachChar] != '_') {
    // If a newline or null terminator is found before the next underscore, it is an error
    if (blank[eachChar] == '\0' || blank[eachChar] == '\n') {
      fprintf(stderr,
              "There was an error: the ending underscore for the blank was not found "
              "before the end of the line or the end of the story.\n");
      // Free all of the memory before exiting
      free_parsed_story(myParsed_story);
      free_parsed_story(usedWords);
      free(myStory);
      exit(EXIT_FAILURE);
    }
    eachChar++;
  }
  blank[eachChar] = '\0';
  return eachChar;
}

parsed_story * addUsedWord(parsed_story * usedWords, char * word) {
  /* Adds a word to the list of used words
   */
  usedWords->num_items++;
  usedWords->array =
      realloc(usedWords->array, usedWords->num_items * sizeof(*usedWords->array));
  usedWords->array[usedWords->num_items - 1] = word;
  return usedWords;
}

char ** removeItem(char ** words, size_t index_to_remove, size_t newSize) {
  /* Removes an item from an array of string pointers.
     Removes the item at a given index.  Provided the new size of the array
  */
  size_t arrayIndex = 0;
  // Create a new array
  char ** temp = malloc(newSize * sizeof(*temp));
  // Add all of the words to the new array except the one being removed
  for (size_t eachItem = 0; eachItem <= newSize; eachItem++) {
    if (eachItem != index_to_remove) {
      temp[arrayIndex] = words[eachItem];
      arrayIndex++;
    }
  }
  // Free the memory for the old array
  free(words);
  return temp;
}

catarray_t * removeWord(char * category, char * word, catarray_t * myCatArray) {
  /* Removes a word from a catarray_t given the catarray_t, the category
     the word is in, and the word to be removed
  */
  // Look through the categories to find the right category
  for (size_t eachCat = 0; eachCat < myCatArray->n; eachCat++) {
    if (strcmp(category, myCatArray->arr[eachCat].name) == 0) {
      // Look through the words to find the right word
      for (size_t eachWord = 0; eachWord < myCatArray->arr[eachCat].n_words; eachWord++) {
        if (strcmp(word, myCatArray->arr[eachCat].words[eachWord]) == 0) {
          // Remove the word from the category
          myCatArray->arr[eachCat].n_words--;
          myCatArray->arr[eachCat].words = removeItem(
              myCatArray->arr[eachCat].words, eachWord, myCatArray->arr[eachCat].n_words);
          // Add the word to the dummy category at the end of the category array
          myCatArray->arr[myCatArray->n].n_words++;
          myCatArray->arr[myCatArray->n].words =
              realloc(myCatArray->arr[myCatArray->n].words,
                      myCatArray->arr[myCatArray->n].n_words *
                          sizeof(*myCatArray->arr[myCatArray->n].words));
          myCatArray->arr[myCatArray->n]
              .words[myCatArray->arr[myCatArray->n].n_words - 1] = word;
          break;
        }
      }
      break;
    }
  }
  return myCatArray;
}

parsed_story * parseStory(char * myStory, catarray_t * myCatArray, int do_not_repeat) {
  /* This function parses the story by placing pointers at all
     of the underscores */
  parsed_story * myParsed_story = malloc(sizeof(*myParsed_story));
  myParsed_story->num_items = 1;
  myParsed_story->array =
      malloc(myParsed_story->num_items * sizeof(*myParsed_story->array));
  // Initialize the parsed story to point to the beginning of the story
  myParsed_story->array[0] = myStory;
  parsed_story * usedWords = malloc(sizeof(*usedWords));
  usedWords->array = NULL;
  usedWords->num_items = 0;
  // Create a variable for each character and a boolean that ensures all blanks have an ending underscore
  int eachChar = 0;
  int positiveIntCheck = 0;
  int endChar = 0;
  // Loop through all of the characters in the story
  while (myStory[eachChar] != '\0') {
    // Look for an underscore
    if (myStory[eachChar] == '_') {
      // Find the category and the end of it and set it to Null terminator
      endChar = findCategory(&myStory[eachChar + 1], myParsed_story, usedWords, myStory);
      // Set the first underscore to Null terminator
      myStory[eachChar] = '\0';
      // Increase the space in the parsed story
      myParsed_story->num_items++;
      myParsed_story->array =
          realloc(myParsed_story->array,
                  myParsed_story->num_items * sizeof(*myParsed_story->array));
      // Check if the category is a positive integer
      positiveIntCheck = check_positive_int(&myStory[eachChar + 1]);
      // If not a positive integer: choose word from the category and add to used words
      if (positiveIntCheck == 0) {
        myParsed_story->array[myParsed_story->num_items - 1] =
            (char *)chooseWord(&myStory[eachChar + 1], myCatArray);
        usedWords =
            addUsedWord(usedWords, myParsed_story->array[myParsed_story->num_items - 1]);
        // If not repeating words: remove the word from the Category Array
        if (do_not_repeat == 1) {
          myCatArray = removeWord(&myStory[eachChar + 1],
                                  usedWords->array[usedWords->num_items - 1],
                                  myCatArray);
        }
      }
      // If the category is a positive integer, go find the word in the used words array
      else {
        if (positiveIntCheck > usedWords->num_items) {
          fprintf(stderr, "Error: the backreference in the story is out of bounds.");
          free_parsed_story(myParsed_story);
          free_parsed_story(usedWords);
          freeCatArray(myCatArray);
          free(myStory);
          exit(EXIT_FAILURE);
        }
        myParsed_story->array[myParsed_story->num_items - 1] =
            usedWords->array[usedWords->num_items - positiveIntCheck];
        usedWords = addUsedWord(
            usedWords, usedWords->array[usedWords->num_items - positiveIntCheck]);
      }
      // Move the pointer to the end of the category
      eachChar += endChar + 1;
      // Add the next piece of the story back to the parsed array
      myParsed_story->num_items++;
      myParsed_story->array =
          realloc(myParsed_story->array,
                  myParsed_story->num_items * sizeof(*myParsed_story->array));
      myParsed_story->array[myParsed_story->num_items - 1] = &myStory[eachChar + 1];
    }
    // Move through the story
    eachChar++;
  }
  // Free the memory for the used words
  free_parsed_story(usedWords);
  return myParsed_story;
}

void printStory(parsed_story * myParsed_story) {
  /* Prints a parsed story
   */
  for (int eachItem = 0; eachItem < myParsed_story->num_items; eachItem++) {
    printf("%s", myParsed_story->array[eachItem]);
  }
  free(myParsed_story->array);
  free(myParsed_story);
}

int check_line_for_colon(char * string, int string_length) {
  /* Error checking to ensure that each line has a colon
   */
  if (string[string_length - 1] != ':') {
    fprintf(stderr, "A colon was not found on this line.\n");
    return EXIT_FAILURE;
  }
  int eachChar = 0;
  while (string[eachChar] != '\0') {
    if (string[eachChar] == '\n') {
      fprintf(stderr, "A colon was not found on this line.\n");
      return EXIT_FAILURE;
    }
    eachChar++;
  }
  return EXIT_SUCCESS;
}

catarray_t * parseCatsWords(char * filename, int do_not_repeat) {
  /* Parses words from a file and puts them in their 
     categories in accordance with the file
     Specifically gets everything up until a :, then 
     gets everything up until the newline.
  */
  // Check file isn't empty and open file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "There was an error opening the file.\n");
    exit(EXIT_FAILURE);
  }
  // Initialize the catarray
  catarray_t * myCatArray = malloc(sizeof(*myCatArray));
  myCatArray->n = 0;
  myCatArray->arr = NULL;
  // Initialize for getdelim and getline
  char * curr = NULL;
  size_t linecap = 0;
  int end_loop = 0;
  size_t eachCat;
  // Loop through each segment of the file
  while (end_loop >= 0) {
    // Get string up until colon
    end_loop = getdelim(&curr, &linecap, ':', f);
    // If no errors or end of file is found
    if (end_loop >= 0) {
      // Error Check to ensure a colon is on each line
      if (check_line_for_colon(curr, end_loop) == EXIT_FAILURE) {
        free(curr);
        freeCatArray(myCatArray);
        exit(EXIT_FAILURE);
      }
      // Set the returned colon to a null terminator
      curr[end_loop - 1] = '\0';
      // Loop throught the categories to see if it's already in the array
      eachCat = 0;
      while (eachCat < myCatArray->n) {
        // If it is in the array, free the memory and break
        if (strcmp(myCatArray->arr[eachCat].name, curr) == 0) {
          free(curr);
          break;
        }
        eachCat++;
      }
      // If it isn't in the array add it to the array
      if (eachCat == myCatArray->n) {
        myCatArray->n++;
        myCatArray->arr =
            realloc(myCatArray->arr, myCatArray->n * sizeof(*myCatArray->arr));
        myCatArray->arr[eachCat].name = curr;
        myCatArray->arr[eachCat].n_words = 0;
        myCatArray->arr[eachCat].words = NULL;
      }
      curr = NULL;
      linecap = 0;
      // Get the string up until the new line
      end_loop = getline(&curr, &linecap, f);
      curr[end_loop - 1] = '\0';
      // This adds the next word in the file even if it is a duplicate
      myCatArray->arr[eachCat].n_words++;
      myCatArray->arr[eachCat].words = realloc(
          myCatArray->arr[eachCat].words,
          myCatArray->arr[eachCat].n_words * sizeof(*myCatArray->arr[eachCat].words));
      myCatArray->arr[eachCat].words[myCatArray->arr[eachCat].n_words - 1] = curr;
      curr = NULL;
    }
    // If the end of file was found, free the line
    else {
      free(curr);
    }
  }
  // If do not repeat option, create a dummy category of used words at the end
  if (do_not_repeat == 1) {
    myCatArray->arr =
        realloc(myCatArray->arr, (myCatArray->n + 1) * sizeof(*myCatArray->arr));
    myCatArray->arr[myCatArray->n].name = NULL;
    myCatArray->arr[myCatArray->n].n_words = 0;
    myCatArray->arr[myCatArray->n].words = NULL;
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "There was an error closing the file.\n");
    freeCatArray(myCatArray);
    exit(EXIT_FAILURE);
  }
  return myCatArray;
}
