
extern void enable_interrupts(void); //in boot.S
extern void game_update(void); //in main game file
extern void move(int); //in main game file

const int timer_period = 30000; // 1 millisecond
const int game_update_interval = 1000; // ms between each game update.
int timeout_count = 0;

int button_down = 0;
const volatile int* switches = (volatile int*) 0x04000010;

// Called from the main file at the start of the program
void init_interrupts(void) {
    //Set the timer period
    volatile short* periodl = (volatile short*) 0x04000028;
    volatile short* periodh = (volatile short*) 0x0400002C;
    *periodl = (timer_period - 1) & 0xFFFF;
    *periodh = (timer_period - 1) >> 16;

    //Enable interrupts in timer
    volatile short* timer_ctrl = (volatile short*) 0x04000024;
    *timer_ctrl = 0b111;

    //Enable interrupts in button
    volatile int* btn_interrupt_mask = (volatile int*) 0x040000d8;
    *btn_interrupt_mask = 0b1;

    enable_interrupts(); // Function in boot.S
}


//Called from boot.S
void handle_interrupt(unsigned cause) {  
    if (cause == 16) { // ID for timer interrupt
        volatile short* timer = (volatile short*) 0x04000020;
        *timer = 0;

        if (++timeout_count == game_update_interval) { // Pass every n:th timeout
            timeout_count = 0; //Acknowledges the IRQ
            game_update(); // Calls game update function in main file.
        }
    }
    if (cause == 18) { // ID for button1 interrupt
        button_down = !button_down;
        volatile int* btn_edgecapture = (volatile int*) 0x040000dc;
        *btn_edgecapture = 0; //Acknowledges the IRQ
        if (button_down) {
            move(*switches & 0b1); //Calls move function in main file, passing direction
        }
    }
}