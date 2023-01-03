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
#define TEST_INPUT_ANSWER 19

int main(int argc, char** argv) {
  // File Reading Operations
  errno = 0;
  FILE* fd = read_file(argc, argv);
  if (!fd) {
    return -1;
  }

  char message_input[14] = {'\0'};
  long result = 1;
  char letter;
  puts("Running...");

  letter = fgetc(fd);
  while(letter != '\n') {

    // This is where you start writing code for each challenge

    for (int i = 1; i <= 14; i++) {
      message_input[i - 1] = message_input[i];
    }
    message_input[13] = letter;

    letter = fgetc(fd);
    if (result <= 14) {
      result++;
      continue;
    }

    bool start_packet = true;
    for (int i = 0; i < 14; i++) {
      for (int j = 0; j < 14; j++) {
        // printf("input[i]: %c\ti: %i\tinput[j]: %c\tj: %i\n", message_input[i], i, message_input[j], j);
        if (message_input[i] == message_input[j] && i != j) {
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
