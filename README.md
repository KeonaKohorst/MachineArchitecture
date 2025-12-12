# AVR Assembly & Arduino Labs

This repository contains a collection of COSC211 laboratory exercises demonstrating low-level programming on AVR-based Arduino platforms using inline assembly.

IF YOU ARE A STUDENT CURRENTLY DOING THESE LABS I ADVISE YOU DON'T USE THESE, TRY TO COMPLETE IT ON YOUR OWN FOR BEST LEARNING OUTCOMES.

## Overview

The projects in this repository focus on understanding how high-level Arduino C++ code interfaces with low-level AVR hardware. Each lab explores a different core concept of embedded systems, including register manipulation, arithmetic operations, loops, timers, memory access, and I/O control.

All examples are implemented as Arduino sketches (`.ino`) that combine:
- Arduino C++ for setup, structure, and serial output
- Inline AVR assembly (`asm volatile`) for direct hardware-level control

## Topics Covered

- Inline AVR assembly within Arduino sketches
- Register-level arithmetic (8-bit, 16-bit, and 24-bit operations)
- Looping and branching using AVR instructions
- Multi-byte counters and nested loops
- SRAM reads and writes using `LDS`, `STS`, and `ST`
- Subroutines using `CALL` and `RET`
- Timer configuration and overflow polling
- Even/odd detection using repeated subtraction
- Fibonacci sequence generation in assembly
- PORT and DDR manipulation for hardware output
- Timing analysis using theoretical vs. measured values

## Hardware & Environment

- AVR-based Arduino board (e.g., Arduino Uno)
- Arduino IDE
- Serial Monitor (9600–115200 baud depending on lab)
- Clock speeds tested at 16 MHz and 1 MHz

## Repository Structure

Each lab or submittable is contained in its own Arduino sketch file and includes:
- A detailed header describing the lab objective
- Inline assembly implementing the required logic
- Serial output for verification and debugging
- Comments explaining key assembly instructions and design decisions

## Purpose

This repository serves as:
- A record of COSC211 laboratory submissions
- A reference for AVR assembly patterns and techniques
- A demonstration of low-level embedded programming concepts

## Author

**Keona Gagnier**  
Bachelor of Computer Information Systems  
Okanagan College

---

*All code is intended for educational purposes as part of COSC211 coursework.*
