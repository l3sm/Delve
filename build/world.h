#ifndef WORLD_H
#define WORLD_H
#include <stdbool.h>

enum BlockType { EMPTY, ROCK, UNKNOWN, IRON_ORE, GOLD };

struct Block {
  enum BlockType type;
  int miningProgress;
};
enum Entity { PLAYER };
struct BlockProperties {
  int hardness;
  int breakingPower;
  bool walkable;
  char symbol;
};

extern const struct BlockProperties blockProperties[];
void getMapSize(int *columns, int *rows);

enum BlockType GetFacingBlockType(struct Player *player, int rows, int columns,
                                  struct Block map[rows][columns]);
#endif
