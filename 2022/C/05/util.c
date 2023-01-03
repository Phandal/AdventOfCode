#include <stdio.h>
#include <stdlib.h>

#include "util.h"

FILE* read_file(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: part1 <filename>\n");
    return NULL;
  }
  
  FILE* fd = fopen(argv[1], "r");
  if (fd == NULL) {
    perror("Error");
    return NULL;
  }

  return fd;
}

node_t* node_new(char data) {
  node_t* n = malloc(sizeof(node_t));
  n->data = data;
  n->next = NULL;
  return n;
}

void node_del(node_t* n) {
  free(n);
}

dynamic_stack_t* dynamic_stack_init() {
  dynamic_stack_t* d = malloc(sizeof(dynamic_stack_t));
  d->count = 0;
  d->head = NULL;
  return d;
}

void dynamic_stack_push(dynamic_stack_t* d, char data) {
  d->count++;
  node_t* n = node_new(data);
  n->next = d->head;
  d->head = n;
}

void dynamic_stack_append(dynamic_stack_t* d, char data) {
  node_t* cur = d->head;

  if (cur == NULL) {
    dynamic_stack_push(d, data);
    return;
  }

  d->count++;
  node_t* n = node_new(data);
  while(cur->next != NULL) {
    cur = cur->next;
  }

  cur->next = n;
}

char dynamic_stack_pop(dynamic_stack_t* d) {
  d->count--;
  char data = d->head->data;
  node_t* temp = d->head;
  d->head = d->head->next;
  node_del(temp);
  return data;
}

void dynamic_stack_print(dynamic_stack_t* d) {
  node_t* cur = d->head;
  
  while(cur != NULL) {
    printf("%c", cur->data);
    cur = cur->next;
  }
}

void dynamic_stack_del(dynamic_stack_t* d) {
  for (size_t i = 0; i < d->count; i++) {
    dynamic_stack_pop(d);
  }
  free(d);
}
