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
#define TEST_INPUT_ANSWER 7

int main(int argc, char** argv) {
  // File Reading Operations
  errno = 0;
  FILE* fd = read_file(argc, argv);
  if (!fd) {
    return -1;
  }

  char input[4] = {'\0'};
  long result = 1;
  char letter;

  letter = fgetc(fd);
  while(letter != '\n') {

    // This is where you start writing code for each challenge
    // printf("%c:%li\n", letter, result);

    for (int i = 1; i <= 4; i++) {
      input[i - 1] = input[i];
    }
    input[3] = letter;

    // printf("%s\n", input);

    letter = fgetc(fd);
    if (result <= 4) {
      result++;
      continue;
    }

    bool start_packet = true;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        // printf("input[i]: %c\ti: %i\tinput[j]: %c\tj: %i\n", input[i], i, input[j], j);
        if (input[i] == input[j] && i != j) {
          start_packet = false;
        }
      }
    }

    if (start_packet) {
      break;
    }
    result++;
    
  }

  printf("Result: %li\n", result);

  // This is where you stop write code

  // Put cleanup code here
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
