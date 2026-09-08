#include "world.h"
#include "player.h"
#include <stdbool.h>
static struct Block outOfBoundsBlock = {.type = UNKNOWN, .miningProgress = 0};
const struct BlockProperties blockProperties[] = {
    [EMPTY] = {.hardness = 0, .breakingPower = 0, .symbol = " "},

    [ROCK] = {.hardness = 4, .breakingPower = 0, .symbol = "\033[90mR\033[0m"},

    [UNKNOWN] = {.hardness = 0,
                 .breakingPower = 0,
                 .symbol = "\033[31m?\033[0m"},

    [IRON_ORE] = {.hardness = 10,
                  .breakingPower = 1,
                  .symbol = "\033[97mI\033[0m"},

    [GOLD] = {.hardness = 2, .breakingPower = 2, .symbol = "\033[93mG\033[0m"}};

void getMapSize(int *columns, int *rows) {
  *columns = 120;
  *rows = 40;
}
struct Block *getFacingBlockType(struct Player *player, int rows, int columns,
                                 struct Block map[rows][columns]) {
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
    return &outOfBoundsBlock;
  } else {
    return &map[targetY][targetX];
  }
}
