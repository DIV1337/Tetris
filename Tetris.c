#include <stdio.h>
#include "Block.h"
#include "Coordinate.h"
#include "BlockLogic.h"
#include <math.h>

int Grid[20][10] = {0}; // 10 columns and 20 rows

Coordinate coords[4];

void printGrid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", Grid[i][j]);
        }
        printf("\n");
    }
}

void readAndUpdateGrid() {
    for (int i = 0; i < BlockArraySize; i++) {
        GetBlockCoordinates(BlockArray[i], coords);
        for (int j = 0; j < 4; j++) {
            Grid[coords[j].y][coords[j].x] = BlockArray[i].type; // Mark the grid with the block type
        }
    }
}

int main(void) {

    spawnBlock();
    printf("Spawned Block!\n");
    readAndUpdateGrid();
    printGrid();
    return 0;
}

