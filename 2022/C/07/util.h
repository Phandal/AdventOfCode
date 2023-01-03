#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

FILE *read_file(int argc, char **argv);

enum { NODE_FILE, NODE_DIRECTORY };

typedef struct NODE {
  int count;
  char* name;
  size_t size;
  int type;
  struct NODE** children;
} node_t;

node_t *node_init(char* name, size_t size, int type);
node_t *node_add(node_t *n, char *name, size_t size, int type);
node_t *node_search_by_valie(node_t *n, char *search_name);
node_t *node_add_by_value(node_t* n, char* search_name, char* name, size_t size, int type);
void node_remove(node_t* n);
void node_print(node_t* n, int padding);

#endif // UTIL_H
