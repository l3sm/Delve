#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"
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
void spawnPlayer(int columns, int rows, struct Player *player);
void playerInput(int *exit, struct Player *player,
                 struct Block *facingBlockInfo);
#endif
