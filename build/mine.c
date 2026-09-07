#include "player.h"
#include "world.h"
void mineBlock(struct Block *facingBlockInfo,
               struct BlockProperties *blockProperties[]) {
  enum BlockType blockToMine = facingBlockInfo->type;
  int hardness = blockProperties[blockToMine]->hardness;
  if (blockToMine != UNKNOWN || blockToMine != EMPTY) {
    do {
      facingBlockInfo->miningProgress++;
    } while (facingBlockInfo->miningProgress < hardness);
  }
}
