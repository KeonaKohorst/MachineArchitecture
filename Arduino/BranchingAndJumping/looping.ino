/*
========================================================
Course: COSC211
Lab: Lab 5 - Submittable 1
Author: Keona Gagnier
Filename: looping.ino
Date Created: February 26 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch demonstrates using an inline AVR assembly loop 
to calculate the sum of the numbers 0 through 9 (0 + 1 + 2 + ... + 9 = 45).

The program uses only two registers:
- r22 to accumulate the sum
- r23 as the loop counter

The assembly loop repeatedly adds the counter to the accumulator, 
increments the counter, and checks if the sum has reached the 
final value of 45. When the loop completes, the result is stored 
into SRAM at address 0x211 using the STS instruction.

The setup() function initializes the serial connection at 9600 baud 
so that the final result can be printed using Serial.println(). 
The loop() function executes the assembly code once, prints the 
value from SRAM, and then repeats (though the sum remains constant).

This exercise reinforces:
- Implementing loops in AVR assembly
- Using registers efficiently for iterative calculations
- Storing results in SRAM and interfacing with Arduino I/O
========================================================
*/


void setup() {
  // setup code, runs once:
  Serial.begin(9600);
}

void loop() {
  // main code, to runs repeatedly:
  asm(
    "ldi r22, 0x00\n"
    "ldi r23, 0x01\n"

    "1:"
    "add r22, r23\n"
    "inc r23\n"
    "cpi r22, 45\n"
    "brne 1b\n"

    "sts 0x211, r22"
    : : : "r22", "r23"
  );
  Serial.println(_SFR_MEM8(0x211));
}