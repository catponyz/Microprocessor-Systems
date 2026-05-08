#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t digit = 0;      // current digit shown on display
volatile uint8_t paused = 0;     // 0 = running, 1 = paused

// Variables used to print timer value when the button is pressed
volatile uint16_t saved_tcnt1 = 0;
volatile uint8_t print_flag = 0;
volatile uint8_t saved_state = 0;

// Common cathode 7-segment patterns: bit0=a, bit1=b, ..., bit6=g
const uint8_t seg[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static inline void show_digit(uint8_t n) {
    uint8_t x = seg[n];

    // Segments a-f are connected to PB0-PB5
    PORTB = (PORTB & ~0x3F) | (x & 0x3F);

    // Segment g is connected to PC0
    PORTC = (PORTC & ~0x01) | ((x >> 6) & 1);
}

// Runs every 0.5 seconds when Timer1 reaches OCR1A
ISR(TIMER1_COMPA_vect) {
    if (!paused) {
        digit = (digit + 1) % 10;  // count 0-9 repeatedly
        show_digit(digit);

        // Timing evidence pin: toggles every 0.5 s
        PORTD ^= (1 << PD7);
    }
}

// Runs when the button on PD2 / INT0 is pressed
ISR(INT0_vect) {
    paused ^= 1;              // toggle pause/resume state

    saved_tcnt1 = TCNT1;      // save timer value at button press
    saved_state = paused;
    print_flag = 1;           // print later in loop(), not inside ISR

    // PD6 shows pause state: HIGH = paused, LOW = running
    if (paused)
        PORTD |= (1 << PD6);
    else
        PORTD &= ~(1 << PD6);
}

void setup() {
    Serial.begin(9600);

    DDRB |= 0x3F;        // PB0-PB5 outputs for segments a-f
    DDRC |= (1 << PC0);  // PC0 output for segment g

    DDRD |= (1 << PD6);  // pause indicator output
    DDRD |= (1 << PD7);  // timing evidence output

    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);

    DDRD &= ~(1 << PD2); // PD2 / INT0 input button
    PORTD |= (1 << PD2); // enable internal pull-up resistor

    show_digit(digit);

    /*
       Timer1 configuration for 0.5 second interval:

       CPU clock = 16 MHz
       Prescaler = 256
       Timer frequency = 16,000,000 / 256 = 62,500 Hz
       Timer tick = 1 / 62,500 = 16 us

       Required ticks for 0.5 s = 0.5 / 16 us = 31,250
       OCR1A = 31,250 - 1 = 31,249
    */
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12); // CTC mode, prescaler 256
    OCR1A = 31249;
    TIMSK1 = (1 << OCIE1A);              // enable Timer1 compare interrupt

    // INT0 triggers on falling edge because button press pulls PD2 LOW
    EICRA = (1 << ISC01);
    EIMSK = (1 << INT0);

    sei(); // enable global interrupts
}

void loop() {
    if (print_flag) {
        // Copy ISR-updated values safely
        cli();
        uint16_t value = saved_tcnt1;
        uint8_t state = saved_state;
        print_flag = 0;
        sei();

        if (state) {
            Serial.print("PAUSED at TCNT1 = ");
        } else {
            Serial.print("RESUMED at TCNT1 = ");
        }

        Serial.println(value);
    }
}