#include "world.h"
#include "player.h"
#include <stdbool.h>
static struct Block outOfBoundsBlock = {.type = UNKNOWN, .miningProgress = 0};
const struct BlockProperties blockProperties[] = {
    [EMPTY] = {.hardness = 0,
               .breakingPower = 0,
               .walkable = true,
               .symbol = ' '},

    [ROCK] = {.hardness = 4,
              .breakingPower = 0,
              .walkable = false,
              .symbol = 'R'},

    [UNKNOWN] = {.hardness = 0,
                 .breakingPower = 0,
                 .walkable = false,
                 .symbol = '?'},

    [IRON_ORE] = {.hardness = 10,
                  .breakingPower = 1,
                  .walkable = false,
                  .symbol = 'I'},

    [GOLD] = {
        .hardness = 2, .breakingPower = 2, .walkable = false, .symbol = 'G'}};

void getMapSize(int *columns, int *rows) {
  *columns = 80;
  *rows = 40;
}
struct Block *GetFacingBlockType(struct Player *player, int rows, int columns,
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
