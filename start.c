#include <stdio.h>

enum BlockType { EMPTY, ROCK, UNKNOWN };
enum Entity { PLAYER };

// The starting position should be at the center of the map. The center of the
// map will be found by halfing the rows and halfing the columns. So we have
// 20/2=10, 50/2=25 so the center of the map right now is [10],[25] To make the
// player spawn in that specific position. A struct answers: “What information
// belongs to this one thing?”
// An enum answers: “Which one option from this fixed list is true?”
void getMapSize(int *columns, int *rows) {
  *columns = 50;
  *rows = 20;
}

struct Position {
  int x;
  int y;
};
struct Player {
  int speed;
  struct Position position;
};

void spawnPlayer(int columns, int rows, struct Player *player) {
  player->position.x = columns / 2;
  player->position.y = rows / 2;
}

void playerMove(int *exit, struct Player *player) {
  char move = getchar();
  switch (move) {
  case 'w':
    player->position.y++;
    break;
  case 's':
    player->position.y--;
    break;
  case 'd':
    player->position.x++;
    break;
  case 'a':
    player->position.x--;
    break;
  case 'q':
    *exit = 0;
    break;
  };
}

int main() {
  int columns;
  int rows;
  int exit = 1;

  getMapSize(&columns, &rows);
  printf("\nMap size set at %dx%d\n", columns, rows);

  struct Player player;

  enum BlockType map[rows][columns];

  spawnPlayer(columns, rows, &player);

  printf("Player spawned at %dx%d\n", player.position.x, player.position.y);

  for (int i = rows - 1; i >= 0; i--) {
    for (int j = 0; j < columns; j++) {
      map[i][j] = ROCK;
    }
  }
  int oob;
  do {
    printf("\e[1;1H\e[2J pos: x:%d, y:%d\n", player.position.x,
           player.position.y);
    for (int i = rows - 1; i >= 0; i--) {
      for (int j = 0; j < columns; j++) {
        if (player.position.x == j && player.position.y == i) {
          printf("\033[97m@\033[0m");
        } else {
          switch (map[i][j]) {
          case ROCK:
            printf("\033[90mR\033[0m");
            break;
          case EMPTY:
            printf(" ");
            break;
          default:
            printf("\033[31m?\033[0m");
            break;
          }
        }
      }
      printf("\n");
    }
    int tempx = player.position.x;
    int tempy = player.position.y;
    oob = -1;
    do {
      oob++;
      if (oob > 0) {
        player.position.x = tempx;
        player.position.y = tempy;
      }
      playerMove(&exit, &player);
    } while (exit &&
             (player.position.x >= columns || player.position.y >= rows ||
              player.position.x < 0 || player.position.y < 0));
  } while (exit);

  return 0;
}
