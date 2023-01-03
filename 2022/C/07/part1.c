// 7116 not the answer
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "util.h"

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 95437

int main(int argc, char** argv) {
  // File Reading Operations
  errno = 0;
  FILE* fd = read_file(argc, argv);
  if (!fd) {
    return -1;
  }

  char* input = malloc(MAX_SIZE);
  long result = 1;

  while(fgets(input, MAX_SIZE, fd)) {
    input[strlen(input) - 1] = '\0';

    // This is where you start writing code for each challenge
    printf("%s\n", input);
    
  }

  printf("Result: %li\n", result);

  // This is where you stop write code

  // Put cleanup code here
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
