#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum BlockType { EMPTY, ROCK, UKNOWN };

// The starting position should be at the center of the map. The center of the
// map will be found by halfing the rows and halfing the columns. So we have
// 20/2=10, 50/2=25 so the center of the map right now is [10],[25] To make the
// player spawn in that specific position. A struct answers: “What information
// belongs to this one thing?”
// An enum answers: “Which one option from this fixed list is true?”
void getMapSize(int rows, int columns) {
  rows = 20;
  columns = 50;
}

struct Position {
  int x;
  int y;
};
struct Player {
  int speed;
  struct Position position;
};

void spawnPlayer(int rows, int columns) {
  struct Player player;
  player.position.x = rows / 2 - rows % 2;
  player.position.y = columns / 2 - rows % 2;
}

int main() {
  char rockBuffer[100] = "\033[90mR\033[0m";
  char *rock = strdup(rockBuffer);
  // So instead of using malloc to strlen of rockbuffer+1 I opted for this
  // strdup method that does the exact same. It also copies the contents of
  // rockbuffer to the place in memory pointed by rock. So now rock points to
  // the gray R.
  int rows;
  int columns;

  getMapSize(rows, columns);
  enum BlockType map[rows][columns];

  spawnPlayer(rows, columns);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      map[i][j] = ROCK;
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      switch (map[i][j]) {
      case ROCK:
        printf("%s", rock);
        break;
      case EMPTY:
        printf(" ");
        break;
      default:
        printf("\033[31m?\033[0m");
        break;
      }
    }
    printf("\n");
  }

  free(rock);
  rock = NULL;

  return 0;
}
