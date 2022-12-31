#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 45000

void bubble_sort(long* maxes) {
  long temp;
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = 1; i < 4; ++i) {
      if (maxes[i] > maxes[i - 1]) {
        sorted = false;
        temp = maxes[i - 1];
        maxes[i - 1 ] = maxes[i];
        maxes[i] = temp;
      }
    }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: part2 <filename>\n");
    return 1;
  }

  FILE* fd = fopen(argv[1], "r");
  if (fd == NULL) {
    perror("Error");
    return 1;
  }

  char* input = malloc(MAX_SIZE);
  long total = 0;
  long maxes[4] = {0};

  while(fgets(input, MAX_SIZE, fd)) {
    if (strcmp(input, "\n") != 0) {
      total += atoi(input);
    } else {
      maxes[3] = total;
      bubble_sort(maxes);
      total = 0;
    }
  }

  // Must do this as sometimes the file does not contain a blank extra line
  maxes[3] = total;
  bubble_sort(maxes);

  printf("Max: %li\n", maxes[0] + maxes[1] + maxes[2]);

  free(input);
  fclose(fd);

  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert((maxes[0] + maxes[1] + maxes[2]) == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
