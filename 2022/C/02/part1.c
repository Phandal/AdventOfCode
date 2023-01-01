#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 4096
#define TEST_INPUT_FILENAME "test_input.txt"
#define TEST_INPUT_ANSWER 15

enum { GAME_LOST, GAME_DRAW, GAME_WON, GAME_PENDING };
enum { RPS_ROCK, RPS_PAPER, RPS_SCISSORS };

typedef struct {
  int outcome;
  char elf_char;
  char your_char;
  int elf_rps;
  int your_rps;
} game;

game* game_new() {
  game* g = malloc(sizeof(game));
  g->outcome = GAME_PENDING;
  g->elf_char = ' ';
  g->your_char = ' ';
  g->elf_rps = -1;
  g->your_rps = -1;
  return g;
}

long game_calculate(game* g) {
  long res = 0;
  res += g->outcome * 3;
  res += g->your_rps + 1;

  return res;
}

long game_outcome(game* g) {
  switch (g->elf_char) {
  case 'A':
    g->elf_rps = RPS_ROCK;
    switch (g->your_char) {
    case 'X':
      g->your_rps = RPS_ROCK;
      g->outcome = GAME_DRAW;
      break;
    case 'Y':
      g->your_rps = RPS_PAPER;
      g->outcome = GAME_WON;
      break;
    case 'Z':
      g->your_rps = RPS_SCISSORS;
      g->outcome = GAME_LOST;
      break;
    }
    break;
  case 'B':
    g->elf_rps = RPS_PAPER;
    switch (g->your_char) {
    case 'X':
      g->your_rps = RPS_ROCK;
      g->outcome = GAME_LOST;
      break;
    case 'Y':
      g->your_rps = RPS_PAPER;
      g->outcome = GAME_DRAW;
      break;
    case 'Z':
      g->your_rps = RPS_SCISSORS;
      g->outcome = GAME_WON;
      break;
    }
    break;
  case 'C':
    g->elf_rps = RPS_SCISSORS;
    switch (g->your_char) {
    case 'X':
      g->your_rps = RPS_ROCK;
      g->outcome = GAME_WON;
      break;
    case 'Y':
      g->your_rps = RPS_PAPER;
      g->outcome = GAME_LOST;
      break;
    case 'Z':
      g->your_rps = RPS_SCISSORS;
      g->outcome = GAME_DRAW;
      break;
    }
    break;
  }

  long result = game_calculate(g);
  return result;
}

void game_del(game *g) { free(g); }

void game_print(game *g) { printf("%d + %d = %li", g->your_rps + 1, g->outcome * 3, game_calculate(g)); }

void game_reset(game* g) {
  g->outcome = GAME_PENDING;
  g->elf_char = ' ';
  g->your_char = ' ';
  g->elf_rps = -1;
  g->your_rps = -1;
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
  game* g = game_new();
  long result = 0;
  
  while(fgets(input, MAX_SIZE, fd)) {
    // This is where you start writeing code for each challenge

    /*
      How the Scoring works:
      A = Rock
      B = Paper
      C = Scissors

      X = LOSE
      Y = DRAW
      Z = WIN

      Rock = 1
      Paper = 2
      Scissors = 3

      Lost = 0
      Draw = 3
      Win = 6
    */
    input[sizeof(input) - 2] = ' ';
    
    char* token = strtok(input, " ");
    g->elf_char = token[0];
    token = strtok(NULL, " ");
    g->your_char = token[0];

    result += game_outcome(g);

    // game_print(g);
    // printf(" = %li\n", result);
    game_reset(g);
  }

  printf("Result: %li\n", result);

  // This is where you stop write code
  game_del(g);
  free(input);
  fclose(fd);

  // Test Case Here
  if (strcmp(argv[1], TEST_INPUT_FILENAME) == 0 ) {
    assert(result == TEST_INPUT_ANSWER);
    puts("Test Passed!");
  }

  return 0;
}
