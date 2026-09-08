#ifndef BLOCK_H
#define BLOCK_H

enum BlockType { EMPTY, ROCK, UNKNOWN, IRON_ORE, GOLD };

struct Block {
  enum BlockType type;
  int miningProgress;
};

#endif
