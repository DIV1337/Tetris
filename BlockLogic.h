#ifndef BLOCKLOGIC_H
#define BLOCKLOGIC_H

#include "Block.h"
#include "Coordinate.h"

#define MAX_BLOCKS 100

extern int BlockArraySize;
extern Block BlockArray[MAX_BLOCKS];

void spawnBlock(void);
void GetBlockCoordinates(Block block, Coordinate coords[4]);

#endif