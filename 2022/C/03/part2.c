// 7116 not the answer
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 157

typedef struct {
  char* item_list;
  int num_items;
} compartment_t;

typedef struct {
  compartment_t* first_compartment;
  compartment_t* second_compartment;
  char item;
  int priority;
} rucksack_t;

compartment_t * compartment_new() {
  compartment_t* t = malloc(sizeof(compartment_t));
  t->item_list = NULL;
  return t;
}

void compartment_del(compartment_t* t) {
  free(t->item_list);
  free(t);
}

void compartment_fill(compartment_t* t, int start, int end, char* items) {
  char* sub_string = malloc(sizeof(start - end + 1));
  strncpy(sub_string, items + start, end - start);
  t->item_list = sub_string;
  t->num_items = strlen(sub_string);
}

void compartment_print(compartment_t* t) {
  printf("%s : %i", t->item_list, t->num_items);
}

rucksack_t* rucksack_new() {
  rucksack_t* r = malloc(sizeof(rucksack_t));
  r->first_compartment = compartment_new();
  r->second_compartment = compartment_new();
  return r;
}

void rucksack_del(rucksack_t* r) {
  compartment_del(r->first_compartment);
  compartment_del(r->second_compartment);
  free(r);
}

void rucksack_fill(rucksack_t* r, char* items) {
  int num_items = strlen(items);
  compartment_fill(r->first_compartment, 0, (num_items / 2), items);
  compartment_fill(r->second_compartment, ((num_items / 2)), (num_items), items);
}

void rucksack_calculate_item(rucksack_t* r) {
  int first_items[52] = {0};
  for (int i = 0; i < r->first_compartment->num_items + 1; ++i) {
    char first_item = r->first_compartment->item_list[i];
    if (first_item > 91) {
      first_items[first_item - 97 + 26]++;
    } else {
      first_items[first_item - 65]++;
    }
  }

  int second_items[52] = {0};
  for (int i = 0; i < r->second_compartment->num_items + 1; ++i) {
    char second_item = r->second_compartment->item_list[i];
    if (second_item > 91) {
      second_items[second_item - 97 + 26]++;
    } else {
      second_items[second_item - 65]++;
    }
  }

  for (int i = 0; i < 52; i++) {
    // printf("i: %d, first: %d, second %d\n", i, first_items[i], second_items[i]);
    if (first_items[i] > 0 && second_items[i] > 0) {
      if (i < 26) {
        r->item =  i + 65;
        r->priority = i + 1 + 26;
      } else {
        r->item = i + 97 - 26;
        r->priority = i + 1 - 26;
      }
    }
  }
}

void rucksack_print(rucksack_t* r) {
  compartment_print(r->first_compartment);
  printf(" : ");
  compartment_print(r->second_compartment);
  printf(" : %c : %d\n", r->item, r->priority);
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
  rucksack_t* r = rucksack_new();
  
  while(fgets(input, MAX_SIZE, fd)) {
    // This is where you start writeing code for each challenge
    input[strlen(input) - 1] = '\0';

    rucksack_fill(r, input);
    rucksack_calculate_item(r);
    // rucksack_print(r);
    // printf("first: %s:\tsecond: %s\titem: %c\tpriority: %d\tresult: %li\n", r->first_compartment->item_list, r->second_compartment->item_list, r->item, r->priority, result);
    result += r->priority;
  }

  printf("Result: %li\n", result);

  // This is where you stop write code

  // Cleanup
  rucksack_del(r);
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
