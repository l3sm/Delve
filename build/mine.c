#include "player.h"
#include "world.h"
#include <stdio.h>
#include <string.h>
struct MiningProgress {
  int x;
  int y;
  int progress;
};
void mine(enum BlockType *facingBlock,
          struct BlockProperties blockProperties[]) {
  int *facingBlockHardness = blockProperties[facingBlock].hardness;
  int move;

  do {
    move = getchar();
    if (move == 'm') {
      *facingBlockHardness--;
    }
  } while (facingBlockHardness > 0);
}
