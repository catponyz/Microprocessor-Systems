void setup() { 
  pinMode(13, OUTPUT);        
  // Configure digital pin 13 as an output pin
}

void loop() {
  digitalWrite(13, HIGH);     
  // Set pin 13 HIGH, turning the onboard LED ON

  delay(500);                 
  // Wait 500 ms = 0.5 s

  digitalWrite(13, LOW);      
  // Set pin 13 LOW, turning the onboard LED OFF

  delay(500);                 
  // Wait another 500 ms = 0.5 s
}

// blink period is 1 second.