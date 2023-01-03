// 7116 not the answer
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "util.h"

#define MAX_SIZE 4096
#define NUM_STACKS 9
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER "MCD"

void move_crates(dynamic_stack_t** stacks, int num, int from, int to) {
  char crates_to_move[num];
  for (int i = 0; i < num; i++) {
    crates_to_move[i] = dynamic_stack_pop(stacks[from]);
  }
  for (int i = num; i > 0; i--) {
    dynamic_stack_push(stacks[to], crates_to_move[i - 1]);
  }
}

int main(int argc, char** argv) {
  // File Reading Operations
  errno = 0;
  FILE* fd = read_file(argc, argv);
  if (!fd) {
    return -1;
  }

  char* input = malloc(MAX_SIZE);
  char* token;
  char crate[4];
  char result[NUM_STACKS];
  dynamic_stack_t** stacks = malloc(sizeof(dynamic_stack_t*) * 10);

  for (int i = 0; i < NUM_STACKS; i++) {
    stacks[i] = dynamic_stack_init();
  }

  while(fgets(input, MAX_SIZE, fd)) {
    input[strlen(input) - 1] = ' ';

    // This is where you start writing code for each challenge
    if (strcmp(input, " ") == 0) {
      break;
    }
    
    for (size_t i = 0; i < strlen(input); i += 4) {
      strncpy(crate, input + i, 4);
      
      if (crate[1] == ' ' || crate[1] < 65) {
        continue;
      }
      dynamic_stack_append(stacks[i/ 4], crate[1]);
    }
    
  }

  // puts("Before Moving");
  // for (int i = 0; i < NUM_STACKS; i++) {
  //   printf("Stack[%d]: ", i);
  //   dynamic_stack_print(stacks[i]);
  //   printf("\n");
  // }

  while(fgets(input, MAX_SIZE, fd)) {
    int num = 0;
    int from = 0;
    int to = 0;
    input[strlen(input) - 1] = ' ';

    token = strtok(input, " ");
    for (int i = 0; i < 5; i++) {
      token = strtok(NULL, " ");
      switch(i) {
        case 0:
          num = atoi(token);
          break;
        case 2:
          from = atoi(token) - 1;
          break;
        case 4:
          to = atoi(token) - 1;
          break;
      }
    }
    // printf("num: %i\tfrom: %i\tto: %i\n", num, from, to);
    move_crates(stacks, num, from, to);
  }

  // puts("After Moving");
  // for (int i = 0; i < NUM_STACKS; i++) {
  //   printf("Stack[%d]: ", i);
  //   dynamic_stack_print(stacks[i]);
  //   printf("\n");
  // }

  for (int i = 0; i < NUM_STACKS; i++) {
    if (stacks[i]->head == NULL) { continue; }
    result[i] = stacks[i]->head->data;
  }

  printf("Result: %s\n", result);

  // This is where you stop write code

  // Put cleanup code here
  for (int i = 0; i < NUM_STACKS; i++) {
    dynamic_stack_del(stacks[i]);
  }
  free(stacks);
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(strcmp(result, TEST_INPUT_ANSWER) == 0);
    puts("Test Passed!");
  }

  return 0;
}
