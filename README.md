# Microprocessor Systems – AVR & Arduino Projects

This repository contains a set of embedded systems projects implemented on the **Arduino Uno (ATmega328P)**.  
The focus is on **low-level programming, register manipulation, timing analysis, and interrupt-driven design**.

---

## 🚀 Overview

In this project, I implemented multiple tasks using both **Arduino abstractions** and **direct AVR register / assembly programming**.  
Each task explores a different aspect of embedded systems:

- Performance comparison between Arduino API and register-level programming
- CPU register manipulation
- Status register (SREG) analysis
- EEPROM persistence
- Interrupt-driven systems
- Hardware timer configuration
- Parallel I/O control
- Assembly control flow
- SPI communication at register level
- I2C / TWI communication and clock speed analysis
- Oscilloscope-based timing verification and hardware debugging

---

## 🧠 Skills Demonstrated

- Embedded Systems Programming on ATmega328P
- Arduino Uno Hardware Programming
- AVR Register-Level Programming
- AVR Assembly Programming
- Digital I/O Configuration using `DDRB`, `DDRC`, `DDRD`, `PORTB`, `PORTC`, and `PORTD`
- External Interrupts using `INT0`, `EICRA`, and `EIMSK`
- Timer1 Configuration using `TCCR1A`, `TCCR1B`, `OCR1A`, and `TIMSK1`
- Timer1 CTC Mode
- EEPROM Memory Handling
- Status Register Analysis using `SREG`
- SPI Communication using `SPCR`, `SPSR`, `SPDR`, `DDRB`, and `PORTB`
- I2C / TWI Communication using `TWBR`, `TWSR`, `TWCR`, `TWDR`, and `TWAR`
- Oscilloscope-Based Timing Analysis
- Hardware Debugging and Signal Validation

---

## 📂 Project Structure

```text
Microprocessor-Systems/
│
├── task 1/
├── task 2/
├── task 3/
├── task 4/
├── task 5/
├── task 6/
├── task 7/
├── task 8/
│
├── report part 1.pdf
├── report part 2.pdf
└── README.md
```

---

## 📌 Tasks

### 🔹 Task 1 – LED Control & Performance Comparison
- Implemented LED blinking at 1 Hz using:
  - Arduino API (`digitalWrite`)
  - Direct register manipulation (`DDRB`, `PORTB`)
- Measured output using oscilloscope
- Achieved ~**2 MHz switching frequency** using register-level control
- Demonstrated performance difference due to software abstraction overhead

🎥 Demo: https://youtu.be/vFGZvdHZfvw  
📂 Code: [Task 1](./task%201)

---

### 🔹 Task 2 – Register-Based Arithmetic & SREG Analysis
- Implemented subtraction using **AVR assembly only**
- Used registers (`r16`, `r17`, `r18`)
- Extracted and analyzed **SREG flags (Zero & Carry)**
- Demonstrated unsigned underflow behavior

🎥 Demo: https://youtu.be/MVslhocQjsk  
📂 Code: [Task 2](./task%202)

---

### 🔹 Task 3 – EEPROM-Based Persistent Counter
- Built a counter incrementing every 1 second using assembly
- Stored value in **EEPROM (address 0x00)**
- Implemented serial commands:
  - `S` → store value
  - `R` → reset value
- Counter resumes after power cycle

🎥 Demo: https://youtu.be/aRZXXDCt_II  
📂 Code: [Task 3](./task%203)

---

### 🔹 Task 4 – Interrupt-Driven Timing System
- External interrupt (INT0 on D2) triggers event
- Timer1 configured in **CTC mode**
- Generated precise **10 ms pulse using 1 ms interrupts**
- Measured output (~10.02 ms) using oscilloscope

🎥 Demo: https://youtube.com/shorts/ENXRU7N97Mo  
📂 Code: [Task 4](./task%204)

---

### 🔹 Task 5 – AVR Control Flow (RJMP, JMP, IJMP)
- Implemented a **multi-mode LED system**
- Used:
  - `RJMP` → polling loop
  - `JMP` → mode switching
  - `IJMP` → runtime dispatch via jump table
- Modes include:
  - Slow blink
  - Double blink
  - Fast strobe

🎥 Demo: https://youtu.be/1SXA7yWFKLQ  
📂 Code: [Task 5](./task%205)

---

### 🔹 Task 6 – Timer-Based 7-Segment Counter
- Controlled a single-digit **7-segment display** using register-level programming
- Display counts from **0 to 9**
- Updated the display every **0.5 seconds** using Timer1 CTC mode
- Used external interrupt (INT0 on D2) to pause and resume the counter
- Verified timing and pause/resume behavior using oscilloscope
- Counter resumes from the same digit after being paused

🎥 Demo: https://youtu.be/4C4q3dPMt78  
📂 Code: [Task 6](./task%206)

---

### 🔹 Task 7 – SPI Communication Between Two Arduinos
- Implemented register-level **SPI communication** between two Arduino Uno boards
- One Arduino acts as Master and the other as Slave
- Master sends decimal values every 1 second:
  - `85`
  - `170`
  - `255`
- Slave receives the values and displays them on the Serial Monitor
- Configured SPI using registers (`SPCR`, `SPSR`, `SPDR`, `DDRB`, `PORTB`)
- Observed SS, SCK, MOSI, and MISO signals using oscilloscope

🎥 Demo: https://youtu.be/fSw1YmivDls  
📂 Code: [Task 7](./task%207)

---

### 🔹 Task 8 – I2C / TWI Communication & Speed Analysis
- Implemented two-way **I2C / TWI communication** between two Arduino Uno boards
- Each board has a push button and LED
- Pressing one board’s button sends a message to turn on the other board’s LED
- Designed a simple message protocol using values:
  - `0x00` → no button pressed / LED off
  - `0x01` → Master button pressed
  - `0x02` → Slave button pressed
- Tested I2C clock speeds around **100 kHz** and **400 kHz**
- Compared SDA and SCL waveforms using different pull-up resistors
- Analyzed how pull-up resistance, capacitance, and wiring affect signal quality

🎥 Demo: https://youtu.be/ayUupy_fTOI  
📂 Code: [Task 8](./task%208)

---

## 📄 Full Report

A detailed technical report (including timing analysis, register explanations, and oscilloscope evidence) is available here:

👉 [Lab Report Part 1](./report%20part%201.pdf)  
👉 [Lab Report Part 2](./report%20part%202.pdf)

---

## 🔧 Hardware Used

- Arduino Uno (ATmega328P)
- Oscilloscope (SIGLENT SDS1202X-E)
- Push buttons
- Onboard LED (D13)
- Single-digit 7-segment display
- Breadboard and jumper wires
- External pull-up resistors for I2C testing

---

## 📚 References

- ATmega328P Datasheet
- AVR Instruction Set Manual
- diagrams.net (flowcharts)

---

## 👩‍💻 Author

**Nargiz Mammadzada**
