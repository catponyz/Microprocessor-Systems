#define F_CPU 16000000UL

#include <avr/io.h>

#define SLAVE_ADDR 0x08        // I2C address of this slave Arduino

// Current message that slave will send to master
volatile uint8_t state = 0x00;

/*
   Main TWI status codes used:

   0x60 = own address + write received
   0x80 = data received from master
   0xA0 = STOP or repeated START received
   0xA8 = own address + read received
   0xC0 = data sent, master returned NACK
*/

void setup() {
  // Set slave address.
  // Address is shifted left because TWAR bit 0 is used for general call enable.
  TWAR = (SLAVE_ADDR << 1);

  // Enable TWI, enable ACK response, and clear TWINT to start listening
  TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);

  // Enable internal pull-ups on SDA = PC4 and SCL = PC5
  PORTC |= (1 << PC4) | (1 << PC5);

  DDRB |= (1 << PB5);   // onboard LED as output
  DDRD &= ~(1 << PD2);  // button input on PD2
  PORTD |= (1 << PD2);  // enable pull-up resistor for button
}

void loop() {
      // Update slave state depending on its own button
      if (!(PIND & (1 << PD2))) {
        state = 0x02;   // tell master to turn its LED on
      } else {
          state = 0x00; // no button pressed
      }

      // TWINT becomes 1 when a TWI event has occurred
      if (TWCR & (1 << TWINT)) {
          // Mask lower 3 bits because they contain prescaler bits
          uint8_t status = TWSR & 0b11111000;

          if (status == 0x60) {
              // Master selected this slave for writing
              TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);

          } else if (status == 0x80) {
              // Master sent one data byte
              uint8_t received = TWDR;

              // 0x01 means master button is pressed, so turn slave LED on
              if (received == 0x01) {
                  PORTB |= (1 << PB5);
              } else {
                  PORTB &= ~(1 << PB5);
              }

              TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);

          } else if (status == 0xA8) {
              // Master selected this slave for reading
              TWDR = state; // send current button state to master

              TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);

          } else {
              // For other TWI states, continue listening and ACK next event
              TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
          }
      }
}