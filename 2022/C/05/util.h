#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

FILE* read_file(int argc, char** argv);

typedef struct node {
  char data;
  struct node* next;
} node_t;

typedef struct {
  size_t count;
  node_t* head;
} dynamic_stack_t;

node_t* node_new(char data);
void node_del(node_t* n);

dynamic_stack_t* dynamic_stack_init();
void dynamic_stack_push(dynamic_stack_t* d, char data);
void dynamic_stack_append(dynamic_stack_t* d, char data);
char dynamic_stack_pop(dynamic_stack_t* d);
void dynamic_stack_print(dynamic_stack_t* d);
void dynamic_stack_del(dynamic_stack_t* d);

#endif // UTIL_H
