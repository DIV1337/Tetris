#ifndef BLOCK_H
#define BLOCK_H

#include <stdbool.h>
#include "Coordinate.h"

typedef struct {
    int x;
    int y;
    int type;
    int rotation;
    Coordinate lowestPoints[4];
    bool isDead;
} Block;

#endif