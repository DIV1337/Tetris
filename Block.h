#ifndef BLOCK_H
#define BLOCK_H

typedef struct { // type: 1 -> oBlock, 2 -> iBlock, 3 -> tBlock, 4 -> lBlock, 5 -> jBlock, 6 -> sBlock, 7 -> zBlock
    int x;
    int y;
    int type;
    int rotation;
} Block;

#endif