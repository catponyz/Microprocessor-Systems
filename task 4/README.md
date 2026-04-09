# Task 4 – Interrupt-Driven Timing System

## 🎯 Objective
- Use interrupt system to generate **exact 10 ms pulse**
- No delay functions allowed

---

## ⚙️ Implementation

- External interrupt:
  - INT0 (D2)
- Timer:
  - Timer1 in CTC mode
- Configuration:
  - Prescaler = 64
  - OCR1A = 249 → 1 ms interrupt

---

## 📊 Key Results

- Countdown = 10 → 10 ms pulse
- Measured pulse:
  - ~**10.02 ms**
- Accurate timing using hardware interrupts

---

## 🔬 Hardware Setup

- Button → D2
- Output → D13
- Oscilloscope for measurement

---

## 🎥 Demo
https://youtube.com/shorts/ENXRU7N97Mo

---

## 🧠 Key Learning

- Interrupts enable precise timing
- Hardware timers are more reliable than delays
- Clearing flags (OCF1A) is critical for accuracy
