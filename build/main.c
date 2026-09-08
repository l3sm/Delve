#include "block.h"
#include "player.h"
#include "terminal.h"
#include "world.h"
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/*
gcc -std=c11 -Wall -Wextra -fsanitize=address main.c player.c terminal.c world.c
yyyyyyyyo start
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
    printf("West ");
    break;
  case EAST:
    printf("East ");
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
void initializeMap(int rows, int columns, struct Block map[rows][columns]) {
  for (int i = rows - 1; i >= 0; i--) {
    for (int j = 0; j < columns; j++) {
      if (i > rows * 3 / 4 || i < rows * 1 / 4) {
        if (i % 3 == 0) {
          map[i][j].type = IRON_ORE;
        } else {
          map[i][j].type = ROCK;
        }
      } else if (j < columns * 1 / 4 || j > columns * 3 / 4) {
        if (j % 5 == 0) {
          map[i][j].type = GOLD;
        } else {
          map[i][j].type = ROCK;
        }
      } else {
        map[i][j].type = EMPTY;
      }
      map[i][j].miningProgress = 0;
    }
  }
}
void printInventory(struct Inventory inventory) {
  printf("\n\033[90mRocks\033[0m = %d  \033[97mIron\033[0m = %d  "
         "\033[93mGold\033[0m = %d",
         inventory.rocks, inventory.iron_ore, inventory.gold);
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
  initializeMap(rows, columns, map);

  int oob;
  struct Block *facingBlockInfo;

  do {
    facingBlockInfo = getFacingBlockType(&player, rows, columns, map);
    printf("\e[1;1H\e[Kpos: x:%d, y:%d      ", player.position.x,
           player.position.y);
    printDirection(&player, facingBlockInfo->type);
    printInventory(player.inventory);
    printf("\e[K\n");
    for (int i = rows - 1; i >= 0; i--) {
      printf("\e[K");
      for (int j = 0; j < columns; j++) {
        if (player.position.x == j && player.position.y == i) {
          printf("\033[92m@\033[0m");
        } else {
          printf("%s", blockProperties[map[i][j].type].symbol);
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
      playerInput(&exit, &player, facingBlockInfo, &player.inventory);
    } while (exit &&
             (player.position.x >= columns || player.position.y >= rows ||
              player.position.x < 0 || player.position.y < 0 ||
              map[player.position.y][player.position.x].type != EMPTY));
  } while (exit);
  return 0;
}
