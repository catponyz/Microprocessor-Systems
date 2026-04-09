# Task 3 – EEPROM Persistent Counter

## 🎯 Objective
- Increment counter every 1 second
- Store value in EEPROM
- Restore value after power reset

---

## ⚙️ Implementation

- Assembly instructions:
  - `LDS`, `INC`, `STS`
- EEPROM registers:
  - `EECR`, `EEAR`, `EEDR`

- Commands:
  - `S` → save to EEPROM
  - `R` → reset

---

## 📊 Key Results

- Increment operation:
  - ~5 CPU cycles (~312.5 ns)
- Counter persists after restart
- EEPROM address used: `0x00`

---

## ⚠️ Limitations

- EEPROM has limited write cycles
- Counter is 8-bit (0–255 overflow)

---

## 🎥 Demo
https://youtu.be/aRZXXDCt_II

---

## 🧠 Key Learning

- EEPROM enables non-volatile storage
- Assembly operations are extremely fast compared to delays
- Most time is spent in delays and I/O, not computation
