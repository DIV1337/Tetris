#include <time.h>

void customDelay(int milliseconds) {
    clock_t start = clock();

    while ((double)(clock() - start) / CLOCKS_PER_SEC < milliseconds / 1000.0) {
        // Wait x milliseconds. Used to have a delay on the updates in main withoput sleeping the system.
    }
}