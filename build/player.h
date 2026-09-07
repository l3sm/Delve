#ifndef PLAYER_H
#define PLAYER_H
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
void playerMove(int *exit, struct Player *player,
                struct BlockType *facingBlockPtr);
#endif
