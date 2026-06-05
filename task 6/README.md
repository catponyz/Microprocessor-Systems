# Task 6 – Timer-Based 7-Segment Counter

## 🎯 Objective
- Control a single-digit **7-segment display**
- Count from **0 to 9**
- Update the display every **0.5 seconds**
- Use a button to pause and resume the counter

---

## ⚙️ Implementation

- Display:
  - Segments `a–f` → `PB0–PB5`
  - Segment `g` → `PC0`

- Timer:
  - Timer1 in CTC mode
  - Prescaler = 256
  - `OCR1A = 31249` → 0.5 second interrupt

- Button:
  - INT0 on D2
  - Falling-edge interrupt
  - Pressing button toggles pause/resume

---

## 📊 Key Results

- Counter updates every **0.5 seconds**
- Counter resets after reaching 9
- Pause does not reset the digit
- Counter resumes from the same digit
- Oscilloscope confirmed timing behavior

---

## 🔬 Hardware Setup

- Arduino Uno (ATmega328P)
- Single-digit 7-segment display
- Push button → D2
- Segment outputs → PB0–PB5 and PC0
- Oscilloscope evidence:
  - PD7 → timing signal
  - PD6 → pause-state signal

---

## 🎥 Demo
https://youtu.be/4C4q3dPMt78

---

## 🧠 Key Learning

- Timer interrupts provide accurate periodic updates
- 7-segment displays can be controlled using parallel I/O
- External interrupts allow responsive pause/resume behavior
- Hardware timers are more reliable than software delays
