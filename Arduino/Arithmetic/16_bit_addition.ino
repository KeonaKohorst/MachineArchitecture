/*
========================================================
Course: COSC211
Lab: Lab 3 - Submittable 1
Author: Keona Gagnier
Filename: 16_bit_addition.ino
Date Created: January 29 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch demonstrates performing a 16-bit addition
using inline AVR assembly. The two 16-bit values 0x1234 and 
0xABCD are added together within the setup() function, with 
the result stored in two registers.

The code initializes the serial connection at 9600 baud to allow
printing of results. After the assembly addition, the upper 
and lower bytes of the result are read from the appropriate 
registers, combined into a 32-bit integer, and printed to the 
serial monitor using Serial.println(). 

The loop() function is left empty, as the addition and output 
are performed once at startup. The final output should match 
the expected 16-bit addition result: 0xBE01 (48,641 in decimal).

This exercise reinforces:
- Using inline AVR assembly within Arduino C++
- Register-level operations and carry handling for multi-byte arithmetic
- Interfacing low-level computations with high-level Arduino I/O
========================================================
*/



void setup() {
  Serial.begin(9600);

  asm("ldi r29, 0x34"); //52 //n1 lower
  asm("ldi r31, 0x12"); //18 //n2 upper
  asm("ldi r30, 0xCD"); //205  //n2 lower
  asm("ldi r28, 0xAB"); //171 //n2 upper

  asm("add r29, r30");
  asm("adc r31, r28");

  //r17 and r16 are the final answer
  uint32_t volatile upper = _SFR_MEM8(31);
  upper = upper << 8;
  uint32_t volatile lower = _SFR_MEM8(29);
  Serial.println(upper + lower);

  delay(1000);
}
