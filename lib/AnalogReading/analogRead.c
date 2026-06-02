#include <avr/io.h>

/*
  ADMUX
  ADC Multiplexer Selection Register
  This register has two jobs:
  Job 1 — Reference voltage (top bits)
  The REFS1 and REFS0 bits tell the ADC what voltage counts as maximum. You set REFS0 to 1 to use 5V as your reference.
  Job 2 — Channel selection (bottom bits)
  The bottom 4 bits tell the multiplexer which of the 6 pins to connect to the ADC circuit. Writing 0 reads A0, writing 3 reads A3, etc.
*/

/* 
  ADCSRA
  ADC Control and Status Register A
  This register also has two jobs:
  Job 1 — Configuration (you write these)

  ADPS2, ADPS1, ADPS0 — set the prescaler (clock speed)
  ADEN — turn the ADC on or off
  ADSC — start a conversion

  Job 2 — Status (hardware writes these)
  ADSC — hardware clears this back to 0 when conversion finishes. This is the same bit you set to start — you write 1 to start it, hardware writes 0 when done.
*/

/*
  ADPS2, 1, 0, are all used for the division frequency. When all 3 are enabled, its 128, which is what we need
  for my microcontroller.
*/

void initADC() {
  // 1. Set our reference voltage which is 5. We do this by using 0, 1 in refs1 and refs 0
  // 2. Set the frequency to read it (128)
  // 3. Enable it

  ADMUX |= (1 << REFS0); // 1.
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set 128 divisoon for the prescaler 2.
  ADCSRA |= (1 << ADEN); // 3. Aden is a pin which when 1 is enabled 0 is off
}

/*
  0xf0 is 1111 0000. This is used to clear the previous channel so we can read from our current channel
  ADSC stands for ADC start conversion
*/

uint16_t readADC(uint8_t channel) {
  // 1. Set the channel to read from (0 - 5, this is the pin essentially)
  // 2. Start the ADC conversion
  // 3. Wait until the conversion is done
  // 4. Return ADC, the value of our conversion.

  ADMUX = (0xf0 & ADMUX) | channel;  
  ADCSRA |= (1 << ADSC);

  while (ADCSRA & (1 << ADSC)) {}; // Waits until the conversion is done.
  return ADC; // 4.
}