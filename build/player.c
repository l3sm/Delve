#include "player.h"
#include "mine.h"
#include "world.h"
#include <stdio.h>
void spawnPlayer(int columns, int rows, struct Player *player) {
  player->position.x = columns / 2;
  player->position.y = rows / 2;
  player->facingDirection = NORTH;
}

void playerInput(int *exit, struct Player *player,
                 struct Block *facingBlockInfo) {
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
  case 'm':
    mineBlock(facingBlockInfo);
    break;
  };
}
