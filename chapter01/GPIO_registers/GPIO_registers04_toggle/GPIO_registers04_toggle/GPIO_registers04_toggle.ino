void setup() {
  DDRB |=  (1 << PB5);  // Set D11 as a OUTPUT
}

void loop() {
  PORTB |=  (1 << PB5);    // LED ON -> D11
  delay(1000);
  PORTB &= ~(1 << PB5);    // LED OFF -> D11
  delay(1000);
}
