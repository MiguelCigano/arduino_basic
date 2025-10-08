volatile int count = 0;

void setup() {
  Serial.begin(9600);
  DDRB &= ~(1 << PB4); // Set D10 as a INPUT 
  DDRB |= (1 << PB5);  // Set D11 as a OUTPUT
  
  // Habilita el PCINT para el D10
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT4); // PCINT4
}

ISR(PCINT0_vect) {
  PORTB ^= (1 << PB5);
  // digitalWrite(11,!digitalRead(11));
  count++;
}

void loop() {
  Serial.println(count);
}