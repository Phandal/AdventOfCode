#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main(void) {
  node_t* root = node_init("/", 0, NODE_DIRECTORY);
  node_add(root, "file1.txt", 6799, NODE_FILE);
  node_add(root, "dir1", 0, NODE_DIRECTORY);
  node_t* child2 = node_add(root, "dir2", 0, NODE_DIRECTORY);
  node_add(child2, "file2.txt", 78999, NODE_FILE);
  node_add_by_value(root, "dir2", "test_file.txt", 89898, NODE_FILE);

  node_print(root, 0);

  node_remove(root);

  return 0;
}
