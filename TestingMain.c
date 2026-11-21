
extern void init_interrupts(void);
extern void testing_main(void);

void set_leds(int led_mask) {
  volatile int* leds = (volatile int*) 0x04000000;
  *leds = led_mask;
}
int led_mask = 0;
void toggle_leds() {
    led_mask = !led_mask;
    set_leds(!led_mask);
}

void game_update() {
    toggle_leds();
}

void move(int direction) {
    toggle_leds();
}

int main() {
    init_interrupts();
    testing_main();
}