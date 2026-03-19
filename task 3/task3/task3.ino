#include <Arduino.h>   // Provides setup(), loop(), Serial, delay(), and basic Arduino types
#include <avr/io.h>    // Provides AVR register definitions such as EECR, EEAR, EEDR, EEPE, EEMPE, EERE

// ─────────────────────────────────────────────
// EEPROM address used to persist the counter
// Physical EEPROM byte address 0x00
// ─────────────────────────────────────────────
#define EEPROM_ADDR 0x00

volatile uint8_t counter = 0; 
// 'volatile' is not strictly necessary here because 'counter' is not modified
// by an interrupt or hardware register. It is kept for safety in case the code
// is later extended with interrupts.

// ── EEPROM helpers (raw register access) ──────
uint8_t eeprom_read_byte_raw(uint16_t addr) {
  while (EECR & (1 << EEPE));   // Wait until any previous EEPROM write finishes
  EEAR = addr;                  // Set EEPROM address register
  EECR |= (1 << EERE);          // Trigger EEPROM read operation
  return EEDR;                  // Return data from EEPROM data register
}

void eeprom_write_byte_raw(uint16_t addr, uint8_t data) {
  while (EECR & (1 << EEPE));   // Wait until any previous EEPROM write finishes
  EEAR = addr;                  // Set EEPROM address register
  EEDR = data;                  // Load data into EEPROM data register
  EECR |= (1 << EEMPE);         // Enable master write (must be set before EEPE)
  EECR |= (1 << EEPE);          // Start EEPROM write
}

void setup() {
  Serial.begin(9600);

  // Restore counter value from EEPROM on power-up.
  // If EEPROM has never been written, the value will be 0xFF,
  // so it is interpreted as an uninitialized value and reset to 0.
  uint8_t stored = eeprom_read_byte_raw(EEPROM_ADDR);
  counter = (stored == 0xFF) ? 0 : stored;

  Serial.print("Resumed from EEPROM. Counter = ");
  Serial.println(counter);
  Serial.println("Commands: S = Store | R = Reset");

  DDRB |= (1 << DDB4);   // Configure PB4 (Arduino pin D12) as output for oscilloscope observation
  PORTB &= ~(1 << PORTB4); // Ensure D12 starts LOW
}

void loop() {
  // ─────────────────────────────────────────────────────────────
  // AVR inline assembly: increment the counter once per loop
  //
  // Instruction breakdown:
  //   LDS r24, counter   → Load value from SRAM into register r24  = 2 cycles
  //   INC r24            → Increment register r24 by 1              = 1 cycle
  //   STS counter, r24   → Store updated value back to SRAM         = 2 cycles
  //
  // TOTAL = 5 CPU cycles
  //
  // At a 16 MHz CPU clock:
  //   1 cycle = 62.5 ns
  //   5 cycles ≈ 312.5 ns
  //
  // This execution time is negligible compared to the 1-second
  // loop window created by delay(1000).
  //
  // The rest of the second (~15,999,995 cycles) is mostly consumed
  // by Serial.print operations and the delay() call.
  //
  // Register used: r24
  // r24 is a caller-saved register and safe for temporary operations.
  //
  // The 'counter' variable resides in SRAM.
  // ─────────────────────────────────────────────────────────────

  asm volatile(
    "lds r24, %[cnt]  \n\t"   // Load counter from SRAM into r24 (2 cycles)
    "inc r24          \n\t"   // Increment r24 (1 cycle)
    "sts %[cnt], r24  \n\t"   // Store updated value back into SRAM (2 cycles)
    :
    : [cnt] "m" (counter)     // Memory operand "m" referring to the counter variable
    : "r24"                   // Inform the compiler that r24 is modified. Clobber
  );

  PORTB ^= (1 << PORTB4);   
  // Toggle PB4 (Arduino D12) once per loop iteration.
  // This produces a square-wave signal visible on an oscilloscope,
  // allowing timing verification of the 1-second loop.

  Serial.print("Counter = ");
  Serial.println(counter);

  // Handle serial commands
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'S') {
      eeprom_write_byte_raw(EEPROM_ADDR, counter);
      Serial.print("Stored counter = ");
      Serial.print(counter);
      Serial.println(" in EEPROM at address 0x00.");
    }

    if (command == 'R') {
      counter = 0;
      eeprom_write_byte_raw(EEPROM_ADDR, 0);
      Serial.println("Counter reset to 0 and saved in EEPROM.");
    }
  }

  delay(1000);  // 1-second loop period
}