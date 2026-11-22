
extern void init_interrupts(void);
extern void update_screen(int[20][10], int);

int grid[20][10];
int score = 0;

void set_leds(int led_mask) {
  volatile int* leds = (volatile int*) 0x04000000;
  *leds = led_mask;
}
int led_mask = 0;
void toggle_leds() {
    led_mask = !led_mask;
    set_leds(!led_mask);
}

int test_counter = 0;

void game_update() {

    toggle_leds();

    //change the grid for testing purposes
    test_counter++;
    score++;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            if ((x * y) % 3 == 0) {
                grid[(y + test_counter) % 20][(x + test_counter) % 10] = (x + y) % 8;
            }
        }
    }

    update_screen(grid, score);
}

void move(int direction) {
    toggle_leds();
}

int main() {
    init_interrupts();
}