// gcc -Wall -Wextra -fsanitize=address start.c terminal.c -o start

#include "terminal.h"
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// Phase 1
enum BlockType { EMPTY, ROCK, UNKNOWN, IRON_ORE, GOLD };
enum Entity { PLAYER };
// The starting position should be at the center of the map. The center of the
// map will be found by halfing the rows and halfing the columns. So we have
// 20/2=10, 50/2=25 so the center of the map right now is [10],[25] To make the
// player spawn in that specific position. A struct answers: “What information
// belongs to this one thing?”
// An enum answers: “Which one option from this fixed list is true?”
void getMapSize(int *columns, int *rows) {
  *columns = 100;
  *rows = 40;
}

struct Position {
  int x;
  int y;
};
enum Direction { NORTH, SOUTH, WEST, EAST };

struct Player {
  int speed;
  struct Position position;
  enum Direction facingDirection;
};

void spawnPlayer(int columns, int rows, struct Player *player) {
  player->position.x = columns / 2;
  player->position.y = rows / 2;
  player->facingDirection = NORTH;
}

void playerMove(int *exit, struct Player *player) {
  int move = getchar();
  switch (move) {
  case 'w':
    player->position.y++;
    player->facingDirection = NORTH;
    break;
  case 's':
    player->position.y--;
    player->facingDirection = SOUTH;
    break;
  case 'd':
    player->position.x++;
    player->facingDirection = EAST;
    break;
  case 'a':
    player->position.x--;
    player->facingDirection = WEST;
    break;
  case 'q':
    *exit = 0;
    break;
  };
}

void printDirection(struct Player *player, enum BlockType facingBlock) {
  printf("Facing Direction: ");
  switch (player->facingDirection) {
  case NORTH:
    printf("North");
    break;
  case SOUTH:
    printf("South");
    break;
  case WEST:
    printf("West");
    break;
  case EAST:
    printf("East");
    break;
  }
  printf("   ");
  printf("Facing Block: ");
  switch (facingBlock) {
  case UNKNOWN:
    printf("Unknown");
    break;
  case ROCK:
    printf("Rock");
    break;
  case IRON_ORE:
    printf("Iron Ore");
    break;
  case GOLD:
    printf("Gold");
    break;
  case EMPTY:
    printf("Nothing");
    break;
  }
}

enum BlockType GetFacingBlockType(struct Player *player, int rows, int columns,
                                  enum BlockType map[rows][columns]) {
  int targetX = player->position.x;
  int targetY = player->position.y;

  switch (player->facingDirection) {
  case NORTH:
    targetY++;
    break;
  case SOUTH:
    targetY--;
    break;
  case WEST:
    targetX--;
    break;
  case EAST:
    targetX++;
    break;
  }

  if (targetX >= columns || targetY >= rows || targetX < 0 || targetY < 0) {
    return UNKNOWN;
  } else {
    return map[targetY][targetX];
  }
}

int main() {
  int columns;
  int rows;
  int exit = 1;
  enableImmediateInput();
  getMapSize(&columns, &rows);
  printf("\e[2J");
  struct Player player;

  enum BlockType map[rows][columns];

  spawnPlayer(columns, rows, &player);

  //  printf("Player spawned at %dx%d\n", player.position.x, player.position.y);

  for (int i = rows - 1; i >= 0; i--) {
    for (int j = 0; j < columns; j++) {
      map[i][j] = ROCK;
    }
  }
  int oob;
  enum BlockType facingBlock = UNKNOWN;
  do {
    facingBlock = GetFacingBlockType(&player, rows, columns, map);
    printf("\e[1;1H\e[Kpos: x:%d, y:%d      ", player.position.x,
           player.position.y);
    printDirection(&player, facingBlock);

    printf("\e[K\n");
    for (int i = rows - 1; i >= 0; i--) {
      printf("\e[K");
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
    fflush(stdout); // Forces any output waiting in the buffer to be sent to the
                    // terminal immidietely, instead of waiting in memory until
                    // the buffer
    // fills up or until the program decides to sent it on its own.

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
