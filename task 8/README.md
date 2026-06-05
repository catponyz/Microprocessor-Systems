# Task 8 – I2C / TWI Communication & Speed Analysis

## 🎯 Objective
- Use two Arduino Uno boards to demonstrate **I2C / TWI communication**
- Send button states between two boards
- Analyze how clock speed and pull-up resistors affect SDA/SCL signals

---

## ⚙️ Implementation

- One Arduino acts as I2C Master
- One Arduino acts as I2C Slave
- Each board has:
  - Push button
  - LED

- TWI registers used:
  - `TWBR`
  - `TWSR`
  - `TWCR`
  - `TWDR`
  - `TWAR`

- Message protocol:
  - `0x00` → no button pressed / LED off
  - `0x01` → Master button pressed
  - `0x02` → Slave button pressed

---

## 📊 Key Results

- Pressing Button A turns on Board B LED
- Pressing Button B turns on Board A LED
- Tested I2C speeds:
  - ~100 kHz
  - ~400 kHz

- Tested pull-up conditions:
  - 330 Ω
  - 2 kΩ
  - No external pull-up

- Stronger pull-ups produced sharper waveforms
- No external pull-ups caused slower rising edges and weaker signal quality

---

## 🔬 Hardware Setup

- Two Arduino Uno boards
- Shared GND between both boards

| Signal | Arduino Pin |
|---|---|
| SDA | A4 |
| SCL | A5 |
| Button | D2 |
| LED | D13 |

- Oscilloscope used to observe:
  - SDA
  - SCL

---

## 🎥 Demo
https://youtu.be/ayUupy_fTOI

---

## 🧠 Key Learning

- I2C uses two lines: SDA and SCL
- I2C lines need pull-up resistors
- Higher clock speeds require faster rise times
- Pull-up resistance, wiring, and capacitance affect signal quality
- Oscilloscope analysis helps detect timing and waveform issues
