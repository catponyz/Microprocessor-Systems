uint8_t a, b;         // Input numbers read from Serial
uint8_t result;       // Stores subtraction result
uint8_t sreg;         // Stores the AVR status register after subtraction
int newData = 0;      // Flag to indicate a complete input line was received

void setup() {
  Serial.begin(9600);
  delay(2000);  
  // Small startup delay so Serial Monitor is ready

  Serial.println("Enter two numbers separated by a space or comma (e.g., 10 20): ");

  DDRB |= (1 << DDB4);   
  // Set PB4 (Arduino digital pin 12) as output for oscilloscope measurement

  PORTB &= ~(1 << PORTB4);  
  // Ensure PB4 starts LOW
}

void loop() {
  if (Serial.available() > 0) {  
    // Check whether serial data has arrived

    a = Serial.parseInt();  
    // Read first integer from Serial input

    b = Serial.parseInt();  
    // Read second integer from Serial input

    if (Serial.read() == '\n') {
      newData = 1;  
      // When Enter/newline is received, mark input as complete
    }
  }

  if (newData == 1) {
    asm volatile (
      "sbi 0x05,4        \n\t"  
      // Set PORTB bit 4 HIGH
      // This creates the start of a pulse on D12 for oscilloscope timing

      "mov r16, %2       \n\t"  
      // Copy input a into register r16

      "mov r17, %3       \n\t"  
      // Copy input b into register r17

      "sub r16, r17      \n\t"  
      // Perform subtraction: r16 = r16 - r17

      "in r18, __SREG__  \n\t"  
      // Copy SREG into register r18 after subtraction

      "mov %0, r16       \n\t"  
      // Store final result from r16 into C variable 'result'

      "mov %1, r18       \n\t"  
      // Store captured SREG from r18 into C variable 'sreg'

      "cbi 0x05,4        \n\t"  
      // Clear PORTB bit 4 LOW
      // This ends the oscilloscope pulse

      : "=r"(result), "=r"(sreg)   // Output operands
      : "r"(a), "r"(b)             // Input operands
      : "r16", "r17", "r18"        // Registers modified inside assembly
    );

    Serial.print("A (input): ");
    Serial.println(a);

    Serial.print("B (input): ");
    Serial.println(b);

    Serial.print("Result (R16): ");
    Serial.println(result);

    Serial.print("SREG: ");
    Serial.println(sreg, BIN);

    Serial.print("Zero Flag (Z): ");
    Serial.println((sreg & (1 << 1)) ? "SET" : "CLEAR");
    // Bit 1 of SREG is the Zero flag

    Serial.print("Carry Flag (C): ");
    Serial.println((sreg & (1 << 0)) ? "SET" : "CLEAR");
    // Bit 0 of SREG is the Carry flag

    newData = 0;
    Serial.println("Enter two numbers separated by a space or comma (e.g., 10 20): ");
  }
}