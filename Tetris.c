#include <stdio.h>

int Grid[20][10] = {0}; // 10 columns and 20 rows

void printGrid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", Grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    
    printGrid();
    return 0;
}