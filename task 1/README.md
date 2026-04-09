# Task 1 – LED Control & Performance Comparison

## 🎯 Objective
Blink the onboard LED (D13) at 1 Hz using:
- Arduino API
- Direct register manipulation

Then measure and compare:
- Execution speed
- Memory overhead
- Maximum switching frequency

---

## ⚙️ Implementation

### Method 1 – Arduino API
- `pinMode(13, OUTPUT)`
- `digitalWrite(HIGH/LOW)`
- `delay(500)`

### Method 2 – Register-Level
- `DDRB` → configure output
- `PORTB` → set/clear pin

---

## 📊 Key Results

- Both methods achieved ~1 Hz
- Register method is more efficient (less abstraction)
- Maximum speed (no delay):
  - ~**2 MHz signal**
  - Based on ~8 CPU cycles per toggle

---

## 🔬 Hardware Setup

- Arduino Uno
- Oscilloscope probe on D13

---

## 🎥 Demo
https://youtu.be/vFGZvdHZfvw

---

## 🧠 Key Learning

- Arduino functions introduce overhead
- Direct register access gives:
  - Faster execution
  - Lower memory usage
- Cycle counting is essential for timing analysis
