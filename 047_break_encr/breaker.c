#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void get_counts(FILE * f, int * counts) {
  int c;
  if ((c = fgetc(f)) == EOF) {
    counts[30]++;
  }
  do {
    if (c >= 'G' && c <= 'z') {
      counts[c - 'G']++;
    }
  } while ((c = fgetc(f)) != EOF);
}

int arg_max(int * values, int length) {
  int max = 0;
  int arg_max = 0;
  for (int i = 0; i < length; i++) {
    if (values[i] > max) {
      max = values[i];
      arg_max = i;
    }
  }
  return arg_max;
}

int decrypt(FILE * f, int * counts) {
  get_counts(f, counts);
  int max_arg = arg_max(counts, 52);
  return (((max_arg - 30) + 26) % 26 + 26) % 26;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Please provide an encrypted file.");
    return EXIT_FAILURE;
  }
  else {
    if (argc > 2) {
      printf("Too many arguments were provided.  We will proceed with finding the "
             "encryption for the first file provided.");
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    int counts[52] = {0};
    printf("%d\n", decrypt(f, counts));
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}
