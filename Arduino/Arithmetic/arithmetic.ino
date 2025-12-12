/*
========================================================
Course: COSC211
Lab: Lab 3 - Submittable 2
Author: Keona Gagnier
Filename: arithmetic.ino
Date Created: January 29 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch demonstrates performing a simple arithmetic
calculation (32 - 16 - 8 - 1) using only the ADD instruction in
inline AVR assembly. The SUB or SUBI instructions are not used;
instead, negative values are generated using the NEG instruction
and then added to the running total.

The setup() function performs the calculation step by step, storing
intermediate values in registers. The final result (7) is stored in
register r27 and printed to the serial monitor using Serial.println().

The loop() function is left empty, as all computation and output
occur once at startup. This exercise reinforces:
- Using inline AVR assembly within Arduino C++
- Performing subtraction via addition of negative values
- Register-level arithmetic and interfacing results with Arduino I/O
========================================================
*/


void setup() {
  Serial.begin(9600);

  asm("ldi r27, 32"); 
  asm("ldi r31, 16"); 
  asm("ldi r30, 8"); 
  asm("ldi r28, 1"); 

  asm("neg r31");
  asm("add r27, r31");

  asm("neg r30");
  asm("add r27, r30");

  asm("neg r28");
  asm("add r27, r28");
  Serial.println(_SFR_MEM8(27));
  
  delay(1000);
}

