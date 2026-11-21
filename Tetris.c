#include <stdio.h>
#include "Block.h"
#include "Coordinate.h"
#include "BlockLogic.h"
#include <math.h>
#include "Grid.h"
#include "Timing.h"
#include <stdlib.h> // Temporary include for rand() function

void updateBlockPosition(Block *block); // initialize
void MoveActiveBlockLeft(void);
void MoveActiveBlockRight(void);

int Grid[20][10] = {0};
bool QuitGame = false;
bool moveActiveBlockLeft = false;
bool moveActiveBlockRight = false;
int randint = 0;

Coordinate coords[4];

void clearGrid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            Grid[i][j] = 0;
        }
    }
}

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
        GetBlockCoordinates(&BlockArray[i], coords);
        for (int j = 0; j < 4; j++) {
            if (coords[j].x >= 0 && coords[j].x < 10 && coords[j].y >= 0 && coords[j].y < 20) {
                Grid[coords[j].y][coords[j].x] = BlockArray[i].type;
            }
        }
    }
}

int main(void) {
    spawnBlock();
    printf("Spawned Block!\n");
    while (!QuitGame) {

        randint = rand() % 10;

        if (randint < 3) {
            moveActiveBlockLeft = true;
        } else if (randint < 6) {
            moveActiveBlockRight = true;
        } else {
            moveActiveBlockLeft = false;
            moveActiveBlockRight = false;
        }


        if (BlockArray[BlockArraySize - 1].isDead) {
            spawnBlock();
            printf("Array size: %d\n", BlockArraySize);
            printf("Spawned Block!\n");
        }

        if (moveActiveBlockLeft) {
            MoveActiveBlockLeft();
        }

        if (moveActiveBlockRight) {
            MoveActiveBlockRight();
        }


        printf("\n");
        printf("\n");
        printf("\n");
        clearGrid();
        readAndUpdateGrid();
        printGrid();


        for (int i = 0; i < BlockArraySize; i++) {
            updateBlockPosition(&BlockArray[i]);
            clearGrid();
            readAndUpdateGrid();
            printGrid();
        }
        
        customDelay(1000);
    }
    
    return 0;
}

