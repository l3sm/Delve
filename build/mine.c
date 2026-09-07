#include "player.h"
#include "world.h"
void mineBlock(struct Block *facingBlockInfo) {
  enum BlockType blockToMine = facingBlockInfo->type;
  int hardness = blockProperties[blockToMine].hardness;
  if (blockToMine != UNKNOWN && blockToMine != EMPTY) {
    facingBlockInfo->miningProgress++;
    if (facingBlockInfo->miningProgress >=
        blockProperties[blockToMine].hardness) {
      facingBlockInfo->type = EMPTY;
      facingBlockInfo->miningProgress = 0;
    }
  }
}
