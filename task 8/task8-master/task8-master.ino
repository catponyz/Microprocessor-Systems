#define F_CPU 16000000UL       // Arduino Uno clock frequency
#define SLAVE_ADDR 0x08        // I2C address of the slave Arduino

/*
   Message protocol:
   0x00 = no button pressed / LED off
   0x01 = master button pressed, turn slave LED on
   0x02 = slave button pressed, turn master LED on
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

void TWI_start() {
    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait until START has been transmitted
    while (!(TWCR & (1 << TWINT)));
}

void TWI_stop() {
    // Send STOP condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8_t data) {
    // Load data or address into TWI Data Register
    TWDR = data;

    // Start transmission and clear TWINT
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until transmission is complete
    while (!(TWCR & (1 << TWINT)));
}

uint8_t TWI_read_nack() {
    // Read one byte and send NACK after receiving it
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until byte is received
    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}

void send_to_slave(uint8_t data) {
    TWI_start();

    // Send slave address with write bit = 0
    TWI_write((SLAVE_ADDR << 1) | 0);

    // Send protocol message to slave
    TWI_write(data);

    TWI_stop();
}

uint8_t request_from_slave() {
    uint8_t data;

    TWI_start();

    // Send slave address with read bit = 1
    TWI_write((SLAVE_ADDR << 1) | 1);

    // Read one byte from slave
    data = TWI_read_nack();

    TWI_stop();

    return data;
}

void setup() {
    /*
       I2C clock setup:

       SCL frequency = F_CPU / (16 + 2 * TWBR * prescaler)

       With F_CPU = 16 MHz and prescaler = 1:
       TWBR = 72 gives approximately 100 kHz
       TWBR = 12 gives approximately 400 kHz
    */
    TWSR = 0x00;   // prescaler = 1

    // TWBR = 72; // standard mode, about 100 kHz
    TWBR = 12;    // fast mode, about 400 kHz

    TWCR = (1 << TWEN); // enable TWI/I2C hardware

    // Enable internal pull-ups on SDA = PC4 and SCL = PC5
    PORTC |= (1 << PC4) | (1 << PC5);

    DDRB |= (1 << PB5);   // onboard LED as output
    DDRD &= ~(1 << PD2);  // button input on PD2
    PORTD |= (1 << PD2);  // enable pull-up resistor for button
}

void loop() {
    // If master button is pressed, send 0x01 to turn slave LED on
    if (!(PIND & (1 << PD2))) {
        send_to_slave(0x01);
    } else {
        send_to_slave(0x00);
    }

    // Ask slave whether its button is pressed
    uint8_t received = request_from_slave();

    // If slave sent 0x02, turn master LED on
    if (received == 0x02) {
        PORTB |= (1 << PB5);
    } else {
        PORTB &= ~(1 << PB5);
    }

    // Small delay to avoid constantly flooding the bus
    _delay_ms(10);
}