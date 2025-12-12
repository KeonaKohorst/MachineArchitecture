/*
========================================================
Course: COSC211
Lab: Lab 5 - Submittable 2
Author: Keona Gagnier
Filename: branching.ino
Date Created: February 26 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch demonstrates using inline AVR assembly to 
determine whether a given number is even or odd. 

The program uses:
- r22 to hold the input number and perform iterative subtraction
- SRAM at address 0x123 to store the final result

The assembly loop repeatedly subtracts 2 from the input number 
until the value is either 0 or 1:
- 0 indicates the original number is even
- 1 indicates the original number is odd

After the loop, the result is stored in SRAM. Outside of the 
assembly block, a simple if/else statement reads the value 
from memory and prints "Number is even!" or "Number is odd!" 
to the Serial monitor.

The setup() function initializes the serial connection at 9600 baud, 
and the loop() function executes the assembly code and prints the result 
once per iteration, with a 1-second delay between loops.

This exercise reinforces:
- Using loops and conditional branches in AVR assembly
- Implementing modular arithmetic using repeated subtraction
- Interfacing register-level calculations with Arduino I/O
========================================================
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  asm(
    "ldi r22, 4\n"

    "1:"
    "cpi r22, 2\n"  //check if less than 2
    "brlt 2f\n"     //if r22 is 1 or 0, leave loop
    "subi r22, 2\n" //otherwise, subtract 2
    "jmp 1b\n"      //continue loop
    
    "2:"
    "sts 0x123, r22"
    : : : "r22"
  );
  if(_SFR_MEM8(0x123) == 0){
    Serial.println("Number is even!");
  }else{
    Serial.println("Number is odd!");
  }
 
  delay(1000);
}