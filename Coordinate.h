#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate coords[4];
} Coordinates;

#endif