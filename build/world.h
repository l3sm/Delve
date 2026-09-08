#ifndef WORLD_H
#define WORLD_H
#include "block.h"
#include "player.h"
#include <stdbool.h>
enum Entity { PLAYER };
struct BlockProperties {
  int hardness;
  int breakingPower;
  const char *symbol;
};

extern const struct BlockProperties blockProperties[];
void getMapSize(int *columns, int *rows);

struct Block *getFacingBlockType(struct Player *player, int rows, int columns,
                                 struct Block map[rows][columns]);
#endif
