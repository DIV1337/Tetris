#include <stdio.h>

volatile char* VGA = (volatile char*) 0x08000000;
volatile int* VGA_CTRL = (volatile int*) 0x04000100;
int backbuffer_frame = 0;

// 11x11 sprite with 3 possible shades for every pixel
char tile_sprite[121] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//color-arrays containing a dark shade, a medium shade and a light shade
char red[3] = {0b01100000, 0b10100000, 0b11100000};
char orange[3] = {0b01100100, 0b10101100, 0b11110000};
char yellow[3] = {0b01101100, 0b10110100, 0b11111100};
char green[3] = {0b00001100, 0b00010100, 0b00011100};
char cyan[3] = {0b00001101, 0b00010110, 0b00011111};
char blue[3] = {0b00000001, 0b00000010, 0b00000011};
char magenta[3] = {0b01100001, 0b10100010, 0b11100011};
char* colors[] = {red, orange, yellow, green, cyan, blue, magenta};

const int background_color = 0b00100101;

void handle_interrupt (unsigned _irq) {

}

void delay(int time) {
    for (int i = 0; i < time; i++) {
        asm volatile ("nop");
    }
}

void set_pixel(int x, int y, int color) {
    y += backbuffer_frame * 240;
    VGA[y*320 + x] = color;
}

void draw_tile(int origin_x, int origin_y, char color_num) {
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 11; y++) {
            char* color = colors[color_num];
            char shade_num = tile_sprite[y*11 + x];
            int pixel_color = color[shade_num];
            set_pixel(origin_x + x, origin_y + y, pixel_color);
        }
    }
}

void update_screen(int grid[200]) {
    backbuffer_frame = !backbuffer_frame;

    //fill all pixels with background color
    for (int i = 0; i < 320*240; i++) {
        VGA[i + backbuffer_frame*320*240] = background_color; 
    }

    //fill the game area with black
    for (int x = 10; x < 120; x++) {
        for (int y = 10; y < 230; y++) {
            set_pixel(x, y, 0);
        }
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            int value = grid[y*10 + x];
            if (value != 0) {
                draw_tile(10 + x*11, 10 + y*11, value - 1);
            }
        }
    }

    //change the start address to current frame and tell it to update
    *(VGA_CTRL+1) = (unsigned int) (VGA + backbuffer_frame*320*240);
    *(VGA_CTRL+0) = 0;

    volatile int* VGA_STATUS = (volatile int*) VGA_CTRL+3;
    //wait until screen is fully updated
    while ((*VGA_STATUS & 0b1) == 1) {
        asm volatile ("nop");
    }
}

int main() {

    int test_counter = 0;

    int test_grid[200];
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            test_grid[y*10 + x] = 0;
        }
    }

    while (1) {

        delay(1000000);

        //change the grid for testing purposes
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 20; y++) {
                if ((x * y) % 3 == 0) {
                    test_grid[y*10 + x + test_counter] = (x + y) % 8;
                }
            }
        }

        //this will be called from the main file
        update_screen(test_grid);

        test_counter++;
    }
}