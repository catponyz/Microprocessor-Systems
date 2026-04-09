# Microprocessor Systems – AVR & Arduino Projects

This repository contains a set of embedded systems projects implemented on the **Arduino Uno (ATmega328P)**.  
The focus is on **low-level programming, register manipulation, timing analysis, and interrupt-driven design**.

---

## 🚀 Overview

In this project, I implemented multiple tasks using both **Arduino abstractions** and **direct AVR register / assembly programming**.  
Each task explores a different aspect of embedded systems:

- Performance comparison (high-level vs low-level)
- CPU register manipulation
- Status register (SREG) analysis
- EEPROM persistence
- Interrupt-driven systems
- Assembly control flow (RJMP, JMP, IJMP)

---

## 🧠 Skills Demonstrated

- Embedded Systems Programming (ATmega328P)
- AVR Register-Level Programming (DDRB, PORTB, EICRA, TCCR1, etc.)
- AVR Assembly (MOV, SUB, IN, INC, IJMP, RJMP, JMP)
- Interrupt Systems (External interrupts, Timer1 CTC)
- Timing Analysis (cycle counting, oscilloscope validation)
- EEPROM Memory Handling
- Hardware Debugging using Oscilloscope

---

## 📂 Project Structure

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

## 📄 Full Report

A detailed technical report (including timing analysis, register explanations, and oscilloscope evidence) is available here:

👉 [Lab Report](./report.pdf)

---

## 🔧 Hardware Used

- Arduino Uno (ATmega328P)
- Oscilloscope (SIGLENT SDS1202X-E)
- Push buttons, onboard LED (D13)

---

## 📚 References

- ATmega328P Datasheet
- AVR Instruction Set Manual
- diagrams.net (flowcharts)

---

## 👩‍💻 Author

**Nargiz Mammadzada**
