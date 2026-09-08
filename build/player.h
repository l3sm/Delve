#ifndef PLAYER_H
#define PLAYER_H
#include "block.h"
struct Position {
  int x;
  int y;
};
struct Inventory {
  int rocks;
  int iron_ore;
  int gold;
};
struct Block;
enum Direction { NORTH, SOUTH, WEST, EAST };

struct Player {
  struct Inventory inventory;
  struct Position position;
  enum Direction facingDirection;
};
void spawnPlayer(int columns, int rows, struct Player *player);
void playerInput(int *exit, struct Player *player,
                 struct Block *facingBlockInfo, struct Inventory *inventory);
struct Inventory *addToInventory(enum BlockType block,
                                 struct Inventory *inventory);
#endif
