# Task 2 – Register-Based Subtraction & SREG Analysis

## 🎯 Objective
- Perform subtraction using **AVR registers only**
- Store result in register
- Analyze **SREG flags (Z and C)**

---

## ⚙️ Implementation

- Registers used:
  - `r16` → operand A
  - `r17` → operand B
  - `r18` → SREG

- Instructions:
  - `mov`
  - `sub`
  - `in (__SREG__)`

---

## 📊 Key Results

| Operation | Result | Z | C |
|----------|--------|---|---|
| 10 - 5   | 5      | 0 | 0 |
| 10 - 10  | 0      | 1 | 0 |
| 5 - 10   | 251    | 0 | 1 |

- Underflow wraps around (8-bit unsigned)
- Carry flag indicates borrow

---

## ⏱ Timing

- Execution time ≈ **500 ns**
- ~8 CPU cycles

---

## 🎥 Demo
https://youtu.be/MVslhocQjsk

---

## 🧠 Key Learning

- AVR uses Carry flag for borrow in subtraction
- SREG is essential for low-level debugging
- Assembly gives full control over operations
