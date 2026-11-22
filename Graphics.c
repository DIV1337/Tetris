#include <stdio.h>

#define TRUE 1

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

const int background_color = 0b01001001;

//Array of unsigned ints representing the 5x5 sprite of a text character. 
//Each bit corresponds with 1 pixel. Range in ASCII is 32 - 90
unsigned int text_sprites[59] = {
    0, 0x401084, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0x64A526, 0xF210A6, 0xF11126, 0x741D07, 0x843D29, 0x743C2F, 0x649C2E,
    0x21110F, 0x649926, 0x643926, 0x20080, 0, 0, 0, 0, 0,
    0, 0x94BD26, 0x749D27, 0xE0842E, 0x74A527, 0xF0BC2F, 0x10BC2F, 
    0xE4B42E, 0x94BD29, 0xE2108E, 0x229084, 0x928CA9, 0xF08421, 0x15AFF71,
    0x11CD671, 0xE8C62E, 0x109D27, 0x1E3A526, 0x1969D27, 0xE8382E, 0x42109F,
    0x64A529, 0x452A31, 0xAFD6B1, 0x1151151, 0x421151, 0x1F1111F
};

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

void draw_char(int origin_x, int origin_y, char character, int color, int scaled) {
    unsigned int sprite = text_sprites[character - 32];
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int value = (sprite >> (x + y*5)) & 0b1;
            if (value) {
                if (scaled) {
                    set_pixel(origin_x + 2*x, origin_y + 2*y, color);
                    set_pixel(origin_x + 2*x + 1, origin_y + 2*y, color);
                    set_pixel(origin_x + 2*x, origin_y + 2*y + 1, color);
                    set_pixel(origin_x + 2*x + 1, origin_y + 2*y + 1, color);
                } else {
                    set_pixel(origin_x + x, origin_y + y, color);
                }
            }
        }
    }
}

void draw_text(int origin_x, int origin_y, char string[], int color, int scaled) {
    int i = 0;
    int character = string[0];
    while (character != 0) { //Loop through string until string terminator NUL is reached
        draw_char(origin_x + i*6 + i*6*scaled, origin_y, character, color, scaled);
        i++;
        character = string[i];
    }
}

char digit_to_char(int digit) {
    return 48 + digit;
}

void int_to_string(int num, char string[]) {
    if (num > 99)
        num = 99;
    int ones = num % 10;
    int tens = (num - ones) / 10;
    if (tens == 0) {
        string[1] = 0;
        string[0] = digit_to_char(ones);
    } else {
        string[1] = digit_to_char(ones);
        string[0] = digit_to_char(tens);
    }
}

void draw_score(int score) {
    char score_string[3] = {0, 0, 0};
    int_to_string(score, score_string);
    draw_text(149, 11, "SCORE: ", 0b0, TRUE);
    draw_text(150, 10, "SCORE: ", 0b11111111, TRUE);
    draw_text(149 + 84, 11, score_string, 0b0, TRUE);
    draw_text(150 + 84, 10, score_string, 0b11111111, TRUE);
}

//Called from the main file after each game_update
void update_screen(int grid[20][10], int score) {
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

    //draw all tiles in the grid
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            int value = grid[y][x];
            if (value != 0) {
                draw_tile(10 + x*11, 10 + y*11, value - 1);
            }
        }
    }

    //draw score text
    draw_score(score);

    //change the start address to current frame and tell it to update
    *(VGA_CTRL+1) = (unsigned int) (VGA + backbuffer_frame*320*240);
    *(VGA_CTRL+0) = 0;

    volatile int* VGA_STATUS = (volatile int*) VGA_CTRL+3;
    //wait until screen is fully updated
    while ((*VGA_STATUS & 0b1) == 1) {
        asm volatile ("nop");
    }
}