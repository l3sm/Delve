#include "player.h"
#include "world.h"
enum BlockType mineBlock(struct Block *facingBlockInfo) {
  enum BlockType blockToMine = facingBlockInfo->type;
  if (blockToMine == UNKNOWN || blockToMine == EMPTY) {
    facingBlockInfo->miningProgress = 0;
    return EMPTY;
  }

  int hardness = blockProperties[blockToMine].hardness;

  facingBlockInfo->miningProgress++;

  if (facingBlockInfo->miningProgress < hardness) {
    return EMPTY;
  }
  facingBlockInfo->type = EMPTY;
  facingBlockInfo->miningProgress = 0;
  return blockToMine;
}
