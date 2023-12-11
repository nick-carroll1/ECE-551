#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

struct _file {
  char ** lines;
  size_t num_lines;
};

typedef struct _file file;

file * load_file(FILE * f) {
  file * this_file = malloc(sizeof(*this_file));
  this_file->num_lines = 0;
  this_file->lines = NULL;
  char * curr = NULL;
  size_t length = 0;
  //Note: what if the file is Null?
  while ((getline(&curr, &length, f)) >= 0) {
    this_file->lines = realloc(this_file->lines,
                               (this_file->num_lines + 1) * sizeof(*(this_file->lines)));
    this_file->lines[this_file->num_lines] = curr;
    this_file->num_lines++;
    curr = NULL;
  }
  //Why do I have to free curr if it is NULL Here?
  free(curr);
  return this_file;
}

void print_file(file * this_file) {
  //Note: what if file is Null?
  for (size_t eachLine = 0; eachLine < this_file->num_lines; eachLine++) {
    printf("%s", this_file->lines[eachLine]);
    free(this_file->lines[eachLine]);
  }
  free(this_file->lines);
  free(this_file);
}

void sort_file(FILE * f) {
  file * this_file = load_file(f);
  sortData(this_file->lines, this_file->num_lines);
  print_file(this_file);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    // read from standard input
    sort_file(stdin);
  }
  else {
    for (int i = 0; i < argc - 1; i++) {
      FILE * f = fopen(argv[i + 1], "r");
      if (f == NULL) {
        perror("Could not open file.\n");
        return EXIT_FAILURE;
      }
      sort_file(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
