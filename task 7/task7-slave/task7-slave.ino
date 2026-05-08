#include <Arduino.h>

void SPI_init_slave() {
  // Configure SPI pins for Slave mode
  DDRB |= (1 << PB4);                              // MISO as output
  DDRB &= ~((1 << PB3) | (1 << PB5) | (1 << PB2)); // MOSI, SCK, SS as inputs

  /*
     SPI Control Register setup:
     SPE = enable SPI

     MSTR is not set, so the Arduino works as SPI Slave.
     The clock is provided by the Master through SCK.
  */
  SPCR = (1 << SPE);
}

void setup() {
  Serial.begin(9600); // Used to display received decimal values
  SPI_init_slave();   // Set Arduino as SPI Slave
}

void loop() {
  // SPIF becomes 1 when one full byte has been received
  if (SPSR & (1 << SPIF)) {
    uint8_t received = SPDR; // Read received byte from SPI Data Register

    // Print the received decimal value: 85, 170, or 255
    Serial.println(received);
  }
}