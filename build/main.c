#include "terminal.h"
#include "world.h"
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
/*
gcc -std=c11 -Wall -Wextra -fsanitize=address main.c player.c terminal.c world.c
-o start
*/
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

int main() {
  int columns;
  int rows;
  int exit = 1;
  enableImmediateInput();
  getMapSize(&columns, &rows);
  printf("\e[2J");
  struct Player player;

  struct Block map[rows][columns];

  spawnPlayer(columns, rows, &player);

  //  printf("Player spawned at %dx%d\n", player.position.x, player.position.y);

  for (int i = rows - 1; i >= 0; i--) {
    for (int j = 0; j < columns; j++) {
      if (i > rows * 3 / 4 || i < rows * 1 / 4) {
        map[i][j].type = ROCK;
        map[i][j].miningProgress = 0;
      } else if (j < columns * 1 / 4 || j > columns * 3 / 4) {
        map[i][j].type = ROCK;
        map[i][j].miningProgress = 0;
      } else {
        map[i][j].type = EMPTY;
      }
    }
  }
  int oob;
  struct Block *facingBlockInfo;
  do {
    facingBlockInfo = GetFacingBlockType(&player, rows, columns, map);
    printf("\e[1;1H\e[Kpos: x:%d, y:%d      ", player.position.x,
           player.position.y);
    printDirection(&player, facingBlockInfo->type);
    printf("\e[K\n");
    for (int i = rows - 1; i >= 0; i--) {
      printf("\e[K");
      for (int j = 0; j < columns; j++) {
        if (player.position.x == j && player.position.y == i) {
          printf("\033[97m@\033[0m");
        } else {
          switch (map[i][j].type) {
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
        break;
      }
      playerInput(&exit, &player, facingBlockInfo);
    } while (exit &&
             (player.position.x >= columns || player.position.y >= rows ||
              player.position.x < 0 || player.position.y < 0 ||
              map[player.position.y][player.position.x].type != EMPTY));
  } while (exit);
  return 0;
}
