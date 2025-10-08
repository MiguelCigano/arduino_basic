int READ; 

void setup() {
  DDRB &= ~(1 << PB4);  // Set D10 as a INPUT 
  DDRB |=  (1 << PB5);  // Set D11 as a OUTPUT
}

void loop() {
  READ = ((PINB >> 4) & (0b00010000 >> 4));
  if (READ) {
    PORTB |=  (1 << PB5);    // LED ON  -> D11
  } 
  else {
      PORTB &= ~(1 << PB5);  // LED OFF -> D11
  }
}
