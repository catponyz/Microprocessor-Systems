void setup() {
  DDRB |= (1 << DDB5);        
  // DDRB = Data Direction Register for Port B
  // DDB5 corresponds to PB5, which is Arduino digital pin 13
  // Setting this bit to 1 makes pin 13 an OUTPUT
}

void loop() {
  PORTB |= (1 << PORTB5);     
  // Set bit 5 of PORTB to 1
  // This drives PB5 HIGH, so the onboard LED turns ON

  delay(500);                 
  // Wait 500 ms = 0.5 s

  PORTB &= ~(1 << PORTB5);    
  // Clear bit 5 of PORTB to 0
  // This drives PB5 LOW, so the onboard LED turns OFF

  delay(500);                 
  // Wait another 500 ms = 0.5 s
}