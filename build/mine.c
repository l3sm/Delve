#include "player.h"
#include "world.h"
enum BlockType mineBlock(struct Block *facingBlockInfo) {
  enum BlockType blockToMine = facingBlockInfo->type;
  int hardness = blockProperties[blockToMine].hardness;
  enum BlockType block;
  if (blockToMine != UNKNOWN && blockToMine != EMPTY) {
    facingBlockInfo->miningProgress++;
    if (facingBlockInfo->miningProgress >= hardness) {
      block = facingBlockInfo->type;
      facingBlockInfo->type = EMPTY;
      facingBlockInfo->miningProgress = 0;
    }
  }
  if (blockToMine == EMPTY) {
    block = EMPTY;
    facingBlockInfo->miningProgress = 0;
  }
  return block;
}
