#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 24000

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: part1 <filename>\n");
    return 1;
  }

  FILE* fd = fopen(argv[1], "r");
  if (fd == NULL) {
    perror("Error");
    return 1;
  }

  char* input = malloc(MAX_SIZE);
  long total = 0;
  long max = 0;

  while(fgets(input, MAX_SIZE, fd)) {
    if (strcmp(input, "\n") != 0) {
      total += atoi(input);
    } else {
      if (total > max) {
        max = total;
      }
      total = 0;
    }
  }

  printf("Max: %li\n", max);

  free(input);
  fclose(fd);

  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(max == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
