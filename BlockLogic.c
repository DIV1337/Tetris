
#include <stdlib.h>
#include "Block.h"
#include "Coordinate.h"
#include "BlockLogic.h"

#define MAX_BLOCKS 100

int BlockArraySize = 0;
Block BlockArray[MAX_BLOCKS];

void spawnBlock(void)
{
    int type = rand() % 7 + 1;

    Block newBlock = {6, 0, type, 0};

    BlockArray[BlockArraySize] = newBlock;
    BlockArraySize++;
}

void GetBlockCoordinates(Block block, Coordinate coords[4])
{
    switch (block.type) {

        case 1: // O-block
            switch (block.rotation) {
                case 0:
                case 90:
                case 180:
                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x,     block.y};
                    coords[2] = (Coordinate){block.x - 1, block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 1};
                    break;

                default:
                    return;
            }
            break;

        case 2: // I-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x + 1, block.y + 1};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x, block.y};
                    coords[1] = (Coordinate){block.x, block.y + 1};
                    coords[2] = (Coordinate){block.x, block.y + 2};
                    coords[3] = (Coordinate){block.x, block.y + 3};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 2, block.y + 2};
                    coords[1] = (Coordinate){block.x - 1, block.y + 2};
                    coords[2] = (Coordinate){block.x,     block.y + 2};
                    coords[3] = (Coordinate){block.x + 1, block.y + 2};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x - 1, block.y + 3};
                    break;

                default:
                    return;
            }
            break;

        case 3: // T-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 2, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 1};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x,     block.y + 1};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x - 1, block.y + 2};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x - 2, block.y + 1};
                    break;

                default:
                    return;
            }
            break;

        case 4: // L-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x,     block.y + 2};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x - 2, block.y + 2};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x - 2, block.y};
                    break;

                default:
                    return;
            }
            break;

        case 5: // J-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x - 2, block.y};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x,     block.y};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 2, block.y + 1};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 2};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 2};
                    coords[3] = (Coordinate){block.x - 2, block.y + 2};
                    break;

                default:
                    return;
            }
            break;

        case 6: // S-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 2, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y};
                    coords[2] = (Coordinate){block.x - 1, block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 1};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x,     block.y};
                    coords[1] = (Coordinate){block.x,     block.y + 1};
                    coords[2] = (Coordinate){block.x - 1, block.y + 1};
                    coords[3] = (Coordinate){block.x - 1, block.y + 2};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 2, block.y + 2};
                    coords[1] = (Coordinate){block.x - 1, block.y + 2};
                    coords[2] = (Coordinate){block.x - 1, block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 1};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x,     block.y};
                    coords[1] = (Coordinate){block.x,     block.y + 1};
                    coords[2] = (Coordinate){block.x - 2, block.y + 1};
                    coords[3] = (Coordinate){block.x - 2, block.y + 2};
                    break;

                default:
                    return;
            }
            break;

        case 7: // Z-block
            switch (block.rotation) {
                case 0:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x,     block.y};
                    coords[2] = (Coordinate){block.x - 2, block.y + 1};
                    coords[3] = (Coordinate){block.x - 1, block.y + 1};
                    break;

                case 90:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 2};
                    break;

                case 180:
                    coords[0] = (Coordinate){block.x - 1, block.y + 1};
                    coords[1] = (Coordinate){block.x,     block.y + 1};
                    coords[2] = (Coordinate){block.x - 2, block.y + 2};
                    coords[3] = (Coordinate){block.x - 1, block.y + 2};
                    break;

                case 270:
                    coords[0] = (Coordinate){block.x - 1, block.y};
                    coords[1] = (Coordinate){block.x - 1, block.y + 1};
                    coords[2] = (Coordinate){block.x,     block.y + 1};
                    coords[3] = (Coordinate){block.x,     block.y + 2};
                    break;

                default:
                    return;
            }
            break;

        default:
            return;
    }
}
