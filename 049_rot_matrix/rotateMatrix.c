#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeMatrix(FILE * f, int height, int width, char matrix[][width]) {
  //int c;
  char temp_str[width + 2];
  for (int i = 0; i < height; i++) {
    if (fgets(temp_str, width + 2, f) == NULL) {
      fprintf(stderr, "Line is missing.");
      exit(EXIT_FAILURE);
    }
    else if (strchr(temp_str, '\n') == NULL) {
      fprintf(stderr, "Line is too long.");
      exit(EXIT_FAILURE);
    }
    else if (strchr(temp_str, '\n') - temp_str < 10) {
      fprintf(stderr, "Line is too short.");
      exit(EXIT_FAILURE);
    }
    else {
      for (int j = 0; j < width; j++) {
        matrix[i][j] = temp_str[j];
        /*while ((c = fgetc(f)) == '\n') {
        continue;
      }
      if (c == EOF) {
        fprintf(stderr, "Error: File is not the appropriate size for matrix.");
        exit(EXIT_FAILURE);
      }
      else {
        matrix[i][j] = c;
	} */
      }
    }
  }
  if (fgets(temp_str, width + 2, f) != NULL) {
    fprintf(stderr, "There are too many lines in this file.");
    exit(EXIT_FAILURE);
  }
}

void rotateMatrix(int height, int width, char matrix[][width]) {
  char tempMatrix[10][10];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      tempMatrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      matrix[i][j] = tempMatrix[height - j - 1][i];
    }
  }
}

void printMatrix(int height, int width, char matrix[][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Please provide an input matrix file.");
    return EXIT_FAILURE;
  }
  else {
    if (argc > 2) {
      printf("Too many arguments were provided.");
      return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    char matrix[10][10];
    initializeMatrix(f, 10, 10, matrix);
    rotateMatrix(10, 10, matrix);
    printMatrix(10, 10, matrix);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}
