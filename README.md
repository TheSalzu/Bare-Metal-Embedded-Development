# AVR Programming

A collection of embedded systems projects, experiments, and reusable drivers developed while learning bare-metal AVR programming in C.

This repository documents my progression from basic microcontroller concepts to more advanced topics such as communication protocols, motor control, real-time clocks, interrupts, timers, and peripheral interfacing. The focus is on understanding how hardware works at a low level by interacting directly with microcontroller registers and external devices.

## Technologies

- C
- AVR Microcontrollers
- PlatformIO
- UART / USART
- SPI
- I2C (TWI)
- Timers
- Interrupts
- PWM
- ADC
- Servo Motors
- Stepper Motors
- Real-Time Clock Modules
- LED Matrix Displays
- Ultrasonic Sensors

## What I Learned

### Embedded Systems Fundamentals
- Register-level programming
- GPIO configuration and control
- Bitwise operations
- Hardware abstraction techniques
- Datasheet interpretation

### Communication Protocols
- UART serial communication
- SPI communication
- I2C communication
- Peripheral integration

### Real-Time Programming
- Interrupt-driven applications
- Timer configuration
- Event-based programming
- PWM generation

### Hardware Interfacing
- Sensors
- Displays
- Motor control
- Real-time clocks

## Featured Project: Custom RTC Library

One of the largest original components in this repository is a Real-Time Clock (RTC) library that I designed and implemented from scratch.

Features:

- I2C communication with RTC hardware
- Time and date retrieval
- Time and date configuration
- Binary-Coded Decimal (BCD) conversions
- Reusable driver structure for integration into other projects

Developing this library required:

- Reading and understanding device datasheets
- Implementing low-level communication routines
- Debugging hardware and software interactions
- Designing a reusable embedded software interface

This project strengthened my understanding of embedded software architecture and communication protocols.

## Example Projects

### RTC Clock Display
Uses a custom RTC driver to retrieve and display current time information.

### Ultrasonic Distance Measurement
Measures distance using ultrasonic sensors and timer-based calculations.

### Servo Motor Control
Generates PWM signals for precise servo positioning.

### LED Matrix Applications
Displays information using a MAX7219-controlled LED matrix.

### Motor Control Experiments
Explores stepper motor and DC motor control techniques.

## Repository Structure

```text
src/
├── Chapters/     # Learning exercises and concept demonstrations
└── Projects/     # Larger integrated projects

lib/              # Reusable libraries and drivers

include/          # Shared headers and definitions