#include <stdio.h>

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
