
#include <stdlib.h>
#include "Block.h"
#include "Coordinate.h"
#include "BlockLogic.h"
#include "Grid.h"
#include <stdio.h>

#define MAX_BLOCKS 100

int BlockArraySize = 0;
Block BlockArray[MAX_BLOCKS];

void spawnBlock(void)
{
    int type = rand() % 7 + 1;

    Block newBlock = {6, 0, type, 0, {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}, false};

    BlockArray[BlockArraySize] = newBlock;
    BlockArraySize++;
}

void GetBlockCoordinates(Block *block, Coordinate coords[4])
{
    switch (block->type) {

        case 1: // O-block
            block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 1};
            block->lowestPoints[1] = (Coordinate){block->x,     block->y + 1};
            block->lowestPoints[2] = (Coordinate){-1, -1};
            block->lowestPoints[3] = (Coordinate){-1, -1};
            switch (block->rotation) {
                case 0:
                case 90:
                case 180:
                case 270:
                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x,     block->y};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 1};
                    break;

                default:
                    return;
            }
            break;

        case 2: // I-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){block->x + 1, block->y + 1};
            
                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x + 1, block->y + 1};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x, block->y + 3};
                    block->lowestPoints[1] = (Coordinate){-1, -1};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x, block->y};
                    coords[1] = (Coordinate){block->x, block->y + 1};
                    coords[2] = (Coordinate){block->x, block->y + 2};
                    coords[3] = (Coordinate){block->x, block->y + 3};
                    break;

                case 180:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 2};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 2};
                    block->lowestPoints[3] = (Coordinate){block->x + 1, block->y + 2};

                    coords[0] = (Coordinate){block->x - 2, block->y + 2};
                    coords[1] = (Coordinate){block->x - 1, block->y + 2};
                    coords[2] = (Coordinate){block->x,     block->y + 2};
                    coords[3] = (Coordinate){block->x + 1, block->y + 2};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 3};
                    block->lowestPoints[1] = (Coordinate){-1, -1};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};


                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x - 1, block->y + 3};
                    break;

                default:
                    return;
            }
            break;

        case 3: // T-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 2, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 1};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x,     block->y + 1};
                    break;

                case 180:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x - 1, block->y + 2};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x - 2, block->y + 1};
                    break;

                default:
                    return;
            }
            break;

        case 4: // L-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};
                    
                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x,     block->y + 2};
                    break;

                case 180:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x - 2, block->y + 2};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x - 2, block->y + 2};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};    
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x - 2, block->y};
                    break;

                default:
                    return;
            }
            break;

        case 5: // J-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x - 2, block->y};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};
                    
                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x,     block->y};
                    break;

                case 180:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 2};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y + 1};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 2};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[1] = (Coordinate){block->x - 2, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 2};
                    coords[3] = (Coordinate){block->x - 2, block->y + 2};
                    break;

                default:
                    return;
            }
            break;

        case 6: // S-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 1};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x,     block->y};
                    coords[1] = (Coordinate){block->x,     block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x - 1, block->y + 2};
                    break;

                case 180:
                    block->lowestPoints[0] = (Coordinate){block->x - 2, block->y};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 1};
                    block->lowestPoints[2] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 2, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 1};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x,     block->y + 1};
                    block->lowestPoints[1] = (Coordinate){block->x - 1, block->y + 2};
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x,     block->y};
                    coords[1] = (Coordinate){block->x,     block->y + 1};
                    coords[2] = (Coordinate){block->x - 1, block->y + 1};
                    coords[3] = (Coordinate){block->x - 1, block->y + 2};
                    break;

                default:
                    return;
            }
            break;

        case 7: // Z-block
            switch (block->rotation) {
                case 0:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 1};    
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y};    
                    block->lowestPoints[2] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x,     block->y};
                    coords[2] = (Coordinate){block->x - 2, block->y + 1};
                    coords[3] = (Coordinate){block->x - 1, block->y + 1};
                    break;

                case 90:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 1};    
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y + 2};  
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 2};
                    break;

                case 180:
                   block->lowestPoints[0] = (Coordinate){block->x - 1, block->y};    
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y};    
                    block->lowestPoints[2] = (Coordinate){block->x - 2, block->y + 1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x,     block->y};
                    coords[2] = (Coordinate){block->x - 2, block->y + 1};
                    coords[3] = (Coordinate){block->x - 1, block->y + 1};
                    break;

                case 270:
                    block->lowestPoints[0] = (Coordinate){block->x - 1, block->y + 1};    
                    block->lowestPoints[1] = (Coordinate){block->x,     block->y + 2};  
                    block->lowestPoints[2] = (Coordinate){-1, -1};
                    block->lowestPoints[3] = (Coordinate){-1, -1};

                    coords[0] = (Coordinate){block->x - 1, block->y};
                    coords[1] = (Coordinate){block->x - 1, block->y + 1};
                    coords[2] = (Coordinate){block->x,     block->y + 1};
                    coords[3] = (Coordinate){block->x,     block->y + 2};
                    break;

                default:
                    return;
            }
            break;

        default:
            return;
    }
}

void updateBlockPosition(Block *block) {

    // Don't move blocks that have already landed
    if (block->isDead) {
        return;
    }

    printf("Updating block position for block type %d at (%d, %d)\n",
           block->type, block->x, block->y);

    for (int i = 0; i < 4; i++) {

        int x = block->lowestPoints[i].x;
        int y = block->lowestPoints[i].y;

        if (x == -1 && y == -1)
            continue;

        printf("lowest[%d] = (%d,%d)\n", i, x, y);
        printf("Checking below (%d,%d): %d\n", x, y + 1, Grid[y + 1][x]);

        if (y + 1 >= 20) {
            printf("Hit bottom\n");
            block->isDead = true;
            return;
        }

        if (Grid[y + 1][x] != 0) {
            printf("Collision!\n");
            block->isDead = true;
            return;
        }
    }
    block->y++;

    printf("Block type %d moved to new position (%d, %d)\n",
           block->type, block->x, block->y);
}

Block *FindActiveBlock() {
    return &BlockArray[BlockArraySize - 1];
}

void MoveActiveBlock(int Left0Right1) {
    Block *activeBlock = FindActiveBlock();
    if (Left0Right1 == 0) {
        activeBlock->x--;
    } else if (Left0Right1 == 1) {
        activeBlock->x++;
    }
    activeBlock-> x--;
}

void RowClearGravity() {
    for (int i = 19; i > 0; i--) {
        for (int j = 0; j < 10; j++) {
            if (Grid[i][j] != 0 && Grid[i + 1][j] == 0) {
                int blockTypePlaceholder = Grid[i][j];
                Grid[i + 1][j] = blockTypePlaceholder;
                Grid[i][j] = 0;
            }
        }

    }
}