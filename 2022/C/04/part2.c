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
#define TEST_INPUT_ANSWER 4

typedef struct {
  int begin;
  int end;
} section;

section* section_new() {
  section* s = malloc(sizeof(section));
  return s;
}

void section_del(section *s) { free(s); }

bool check_unique_section(section* s1, section* s2) {
  if (s2->begin >= s1->begin && s2->begin <= s1->end) {
    return false;
  }
  if (s2->end >= s1->begin && s2->end <= s1->end) {
    return false;
  }

  if (s1->begin >= s2->begin && s1->begin <= s2->end) {
    return false;
  }
  if (s1->end >= s2->begin && s1->end <= s2->end) {
    return false;
  }

  return true;
}

int main(int argc, char** argv) {
  // File Reading Operations
  errno = 0;
  FILE* fd = read_file(argc, argv);
  if (!fd) {
    return -1;
  }
  
  char* input = malloc(MAX_SIZE);
  section* s1 = section_new();
  section* s2 = section_new();
  long result = 0;
  
  while(fgets(input, MAX_SIZE, fd)) {
    // This is where you start writeing code for each challenge
    input[strlen(input) - 1] = '\0';

    char* token1;
    char* token2;

    token1 = strtok(input, ",");
    token2 = strtok(NULL, ",");
  
    s1->begin = atoi(strtok(token1, "-"));
    s1->end = atoi(strtok(NULL, "-"));
    s2->begin = atoi(strtok(token2, "-"));
    s2->end = atoi(strtok(NULL, "-"));

    // printf("%i:%i:%i:%i\n", s1->begin, s1->end, s2->begin, s2->end);

    if(!check_unique_section(s1, s2)) {
      ++result;
    }
    
  }

  printf("Result: %li\n", result);

  // This is where you stop write code

  // Cleanup
  section_del(s1);
  section_del(s2);
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
