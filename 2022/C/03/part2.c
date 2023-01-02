#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 70

enum { RUCK_SACK_1, RUCK_SACK_2, RUCK_SACK_3 };

typedef struct {
  char* rucksack_1;
  char* rucksack_2;
  char* rucksack_3;
} group;

group* group_new() {
  group* g = malloc(sizeof(group));
  g->rucksack_1 = NULL;
  g->rucksack_2 = NULL;
  g->rucksack_3 = NULL;

  return g;
}

void group_del(group* g) {
  if (g->rucksack_1) { free(g->rucksack_1); }
  if (g->rucksack_2) { free(g->rucksack_2); }
  if (g->rucksack_3) { free(g->rucksack_3); }

  free(g);
}

void group_add_rucksack(group* g, char* input, int rucksack_num) {
  switch(rucksack_num) {
  case RUCK_SACK_1:
    g->rucksack_1 = malloc(strlen(input));
    strcpy(g->rucksack_1, input);
    break;
  case RUCK_SACK_2:
    g->rucksack_2 = malloc(strlen(input));
    strcpy(g->rucksack_2, input);
    break;
  case RUCK_SACK_3:
    g->rucksack_3 = malloc(strlen(input));
    strcpy(g->rucksack_3, input);
    break;
  }
}

char group_calculate_badge(group* g) {
  size_t s1 = strlen(g->rucksack_1);
  size_t s2 = strlen(g->rucksack_2);
  size_t s3 = strlen(g->rucksack_3);
  char* common_letters = NULL;
  size_t count = 0;
  char badge_letter;
  
  for(size_t i = 0; i < s1; i++) {
    char l1 = g->rucksack_1[i];

    for (size_t ii = 0; ii < s2; ii++) {
      char l2 = g->rucksack_2[ii];
      
      if (l1 == l2) {
        ++count;
        common_letters = realloc(common_letters, sizeof(char) * count);
        common_letters[count - 1] = l1;
      }
    }
  }

  for (size_t i = 0; i < s3; i++) {
    char l3 = g->rucksack_3[i];

    for (size_t ii = 0; ii < count; ii++) {
      char cl = common_letters[ii];

      if (cl == l3) {
        badge_letter = cl;
      }
    }
  }

  free(common_letters);
  return badge_letter;
}

void group_reset(group* g) {
  g->rucksack_1 = NULL;
  g->rucksack_2 = NULL;
  g->rucksack_3 = NULL;
}

long calculate_priority(char badge_letter) {
  if (badge_letter > 92) {
    return badge_letter - 96;
  } else {
    return badge_letter - 64 + 26;
  }
}

int main(int argc, char** argv) {
  // File Reading Operations
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
  long result = 0;
  int cont = 1;
  group* g = group_new();
  
  while(cont) {
    // This is where you start writeing code for each challenge

    for (int i = 0; i < 3; i++) {
      if (!(fgets(input, MAX_SIZE, fd))) {
        if (i > 0) {
          fprintf(stderr, "Error: EOF reached!\n");
          group_del(g);
          free(input);
          fclose(fd);
          return 1;
        }
        else {
          cont = 0;
          break;
        }
      }
      input[strlen(input) - 1] = '\0';
      group_add_rucksack(g, input, i);
    }

    if (cont) {
      char badge = group_calculate_badge(g);
      result += calculate_priority(badge);
    }
    group_reset(g);
  }

  printf("Result: %li\n", result);

  // This is where you stop write code

  // Cleanup
  group_del(g);
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
