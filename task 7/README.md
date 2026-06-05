# Task 7 – SPI Communication Between Two Arduinos

## 🎯 Objective
- Use two Arduino Uno boards to demonstrate **SPI communication**
- Configure SPI using register-level programming
- Send decimal values from Master to Slave

---

## ⚙️ Implementation

- One Arduino acts as SPI Master
- One Arduino acts as SPI Slave

- SPI registers used:
  - `SPCR`
  - `SPSR`
  - `SPDR`
  - `DDRB`
  - `PORTB`

- Master sends values every 1 second:
  - `85`
  - `170`
  - `255`

---

## 📊 Key Results

- Slave correctly receives values from Master
- Received values are displayed on Serial Monitor
- SPI sequence repeats continuously:

```text
85 → 170 → 255 → repeat
```

- Oscilloscope confirmed SPI activity on:
  - SS
  - SCK
  - MOSI
  - MISO

---

## 🔬 Hardware Setup

- Two Arduino Uno boards
- Shared GND between both boards

| SPI Signal | Arduino Pin |
|---|---|
| MOSI | D11 |
| MISO | D12 |
| SCK | D13 |
| SS | D10 |

---

## 🎥 Demo
https://youtu.be/fSw1YmivDls

---

## 🧠 Key Learning

- SPI uses Master-Slave communication
- Master controls clock using SCK
- SS selects the Slave during transmission
- `SPDR` starts data transfer and stores received data
- Oscilloscope can verify actual transmitted bit patterns
