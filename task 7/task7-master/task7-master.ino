#include <Arduino.h>

void SPI_init_master() {
  // Configure SPI pins for Master mode
  DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS as outputs
  DDRB &= ~(1 << PB4);                          // MISO as input

  // Keep Slave Select HIGH when no transfer is happening
  PORTB |= (1 << PB2);                          // SS HIGH = slave inactive

  /*
     SPI Control Register setup:
     SPE  = enable SPI
     MSTR = select Master mode
     SPR1 = clock divider bit

     With SPR1 = 1 and SPR0 = 0:
     SPI clock = F_CPU / 64
     For Arduino Uno: 16 MHz / 64 = 250 kHz
  */
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);

  // Disable double-speed SPI mode, so clock stays F_CPU / 64
  SPSR &= ~(1 << SPI2X);
}

void SPI_send(uint8_t data) {
  // Writing to SPDR starts the SPI transfer
  SPDR = data;

  // Wait until SPIF becomes 1, meaning the byte transfer is complete
  while (!(SPSR & (1 << SPIF)));

  // Reading SPDR clears SPIF and gets the byte received during transfer.
  // In this task, the Master does not use received data, so it is dummy.
  uint8_t dummy = SPDR;
  (void)dummy;
}

void setup() {
  SPI_init_master(); // Set Arduino as SPI Master
}

void loop() {
  // Required sequence of decimal values
  uint8_t values[3] = {85, 170, 255};

  for (uint8_t i = 0; i < 3; i++) {
    PORTB &= ~(1 << PB2);  // Pull SS LOW to select the slave

    SPI_send(values[i]);   // Send one byte through MOSI

    PORTB |= (1 << PB2);   // Pull SS HIGH to end the transfer

    delay(1000);           // Send next value after 1 second
  }
}