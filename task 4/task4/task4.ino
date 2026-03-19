#include <avr/io.h>
#include <avr/interrupt.h>

// Volatile shared variable between ISRs
volatile uint8_t countdown = 0;

void setup() {
    // ─── Output Pin: D13 (PB5) ───
    DDRB |= (1 << DDB5);       // Set D13 as OUTPUT
    PORTB &= ~(1 << PORTB5);   // Start LOW

    // ─── Input Pin: D2 (PD2) with pull-up ───
    DDRD &= ~(1 << DDD2);      // Set D2 as INPUT
    PORTD |= (1 << PORTD2);    // Enable internal pull-up

    // ─── External Interrupt INT0 (D2) ───
    // Trigger on FALLING edge (button press pulls LOW)
    EICRA |= (1 << ISC01);     // ISC01=1, ISC00=0 → falling edge
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);      // Enable INT0

    // ─── Timer1 CTC Mode, 1ms interval ───
    // F_CPU = 16MHz, Prescaler = 64
    // OCR1A = (16,000,000 / (64 * 1000)) - 1 = 249
    TCCR1A = 0;                         // Clear control register A
    TCCR1B = 0;                         // Clear control register B
    TCNT1  = 0;                         // Reset counter

    OCR1A = 249;                        // Compare match value for 1ms
    TCCR1B |= (1 << WGM12);            // CTC mode (Clear Timer on Compare)
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler = 64
    // Timer interrupt NOT enabled yet — only enable when counting

    sei(); // Enable global interrupts
}

// ─── External Interrupt ISR: Button on D2 ───
ISR(INT0_vect) {
    PORTB |= (1 << PORTB5);    // Set D13 HIGH immediately
    countdown = 10;             // Load 10ms countdown
    TCNT1 = 0;                  // Reset timer counter
    TIFR1 |= (1 << OCF1A);   // clear pending compare flag, before it measurement was 9.02 ms
    TIMSK1 |= (1 << OCIE1A);   // Enable Timer1 compare interrupt
}
// everytime 1 ms passes and compare value = counter OCIE1A enables timer1 func.
// ─── Timer1 Compare ISR: fires every 1ms ───
ISR(TIMER1_COMPA_vect) {
    if (countdown > 0) {
        countdown--;
        if (countdown == 0) {
            PORTB &= ~(1 << PORTB5);   // Set D13 LOW
            TIMSK1 &= ~(1 << OCIE1A); // Disable timer interrupt
        }
    }
}

// ─── Main loop: must remain empty ───
void loop() {
    // Intentionally empty — all logic handled by interrupts
}