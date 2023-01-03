#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

node_t* node_init(char* name, size_t size, int type) {
  node_t* n = malloc(sizeof(node_t));
  n->count = 0;
  n->name = name;
  n->size = size;
  n->type = type;
  n->children = NULL;
  return n;
}

node_t* node_add(node_t* n, char* name, size_t size, int type) {
  n->count++;
  n->children = realloc(n->children, sizeof(node_t) * n->count);
  node_t* c = node_init(name, size, type);
  n->children[n->count - 1] = c;
  return c;
}

node_t* node_search_by_value(node_t* n, char* search_name) {
  if (strcmp(n->name, search_name) == 0) {
    return n;
  }

  node_t* s = NULL;
  for (int i = 0; i < n->count; i++) {
    s = node_search_by_value(n->children[i], search_name);
  }

  return s;
}

node_t* node_add_by_value(node_t* n, char* search_name, char* name, size_t size, int type) {
  node_t* temp = node_search_by_value(n, search_name);
  if (temp == NULL) {
    return NULL;
  }
  node_t* a = node_add(temp, name, size, type);
  return a;
}

void node_remove(node_t* n) {
  for (; n->count != 0; n->count--) {
    node_remove(n->children[n->count - 1]);
  }

  free(n->children);
  free(n);
}

void node_print(node_t* n, int padding) {
  for (int i = 0; i < padding; i++){
    printf(" ");
  }
  printf("Name: %s\tSize: %li\tType: %d\tNum Children: %d\n", n->name, n->size, n->type, n->count);
  for (int i = 0; i < n->count; i++) {
    node_print(n->children[i], padding + 2);
  }
}
