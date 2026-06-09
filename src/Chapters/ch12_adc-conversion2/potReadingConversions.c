// // Includes/Definitions
// #include <avr/io.h>
// #include <avr/sleep.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "USART.h"

// #define POT_PIN PC0
// #define WINDOW_SIZE 4

// // Typedefs
// typedef struct {
//   uint16_t totalValue;
//   uint8_t lastModifiedIndex;
//   uint16_t contents[WINDOW_SIZE];
// } Buffer;

// // Function Definitions
// void initADC();
// uint16_t readAnalog();
// uint16_t oversample16x();
// uint16_t getMovingAverage(uint16_t newSample, Buffer *pBuffer);

// // Interrupts
// EMPTY_INTERRUPT(ADC_vect);

// // Main Code
// int main(void) {
//   initADC();
//   initUSART();
//   sei();

//   // Variables
//   Buffer movingAverageBuffer = {0};

//   // Main loop
//   while (1) {
//     const uint16_t rawValue = readAnalog();
//     const uint16_t oversampledPotValue = oversample16x();
//     const uint16_t movingAverage = getMovingAverage(oversampledPotValue, &movingAverageBuffer);

//     printString("Raw Value: ");
//     printWord(rawValue);
//     printString("\r\n");

//     printString("Oversampled Value: ");
//     printWord(oversampledPotValue);
//     printString("\r\n");

//     printString("Moving Average: ");
//     printWord(movingAverage);
//     printString("\r\n");

//     _delay_ms(3000);
//   }

//   return 0;
// }

// // Functions
// void initADC() {
//   ADMUX |= (1 << REFS0); // Use the 0-5v voltage from the board for ref voltage
//   ADMUX = (ADMUX & 0xF0) | POT_PIN; // Tell the multiplexer which pin is getting read
//   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler
//   ADCSRA |= (1 << ADIE); // Enables the intterup to wake the cpu up when the adc conversion is done
//   ADCSRA |= (1 << ADEN); // Enable the ADC

//   set_sleep_mode(SLEEP_MODE_ADC);
// }

// uint16_t readAnalog() {
//   ADCSRA &= ~(1 << ADIE); // Disable the interrupt
//   ADCSRA |= (1 << ADSC); // Start the read
//   while (ADCSRA & (1 << ADSC)) {}
//   ADCSRA |= (1 << ADIE); // ENable the interrupt
//   return ADC;
// }

// uint16_t oversample16x() {
//   uint16_t oversampledValue = 0;

//   for (uint8_t i = 0; i < 16; i++) {
//     sleep_mode();
//     oversampledValue += ADC;
//   }

//   return oversampledValue >> 2; // shift right 2 = divide by 4 = drop 2 noisy bits
// }

// uint16_t getMovingAverage(uint16_t newSample, Buffer *pBuffer) {
//   pBuffer->lastModifiedIndex = (pBuffer->lastModifiedIndex + 1) % WINDOW_SIZE; // set next index
//   pBuffer->totalValue -= pBuffer->contents[pBuffer->lastModifiedIndex]; // remove oldest
//   pBuffer->contents[pBuffer->lastModifiedIndex] = newSample; // replace with new
//   pBuffer->totalValue += newSample; // add new to total
//   return pBuffer->totalValue / WINDOW_SIZE; // return average
// }