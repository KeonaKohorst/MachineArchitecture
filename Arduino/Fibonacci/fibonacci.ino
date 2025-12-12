
/*
========================================================
Course: COSC211
Lab: Lab 6
Author: Keona Gagnier
Student ID: 300325209
Filename: fibonacci.ino
Date Created: March 4 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch demonstrates calculating Fibonacci numbers 
using inline AVR assembly and storing intermediate results in SRAM.

The program performs the following steps:
1. Initializes the first two Fibonacci numbers (F(n-2) = 0, F(n-1) = 1) 
   in SRAM at addresses 0x0100 and 0x0101.
2. Uses a loop to calculate the next 12 Fibonacci numbers.
3. Each iteration calls an inline assembly subroutine to:
   - Load the previous two Fibonacci values from SRAM into registers.
   - Add them to compute the next Fibonacci value.
   - Update SRAM so that F(n-1) and F(n-2) always hold the last two numbers.
4. After the loop, the final Fibonacci number is printed to the Serial monitor.

The setup() function initializes the serial connection at 9600 baud, 
and the loop() function repeatedly executes the calculation, printing 
the latest Fibonacci number every second.

This exercise reinforces:
- Using inline AVR assembly within Arduino C++
- Implementing subroutines with call and ret
- Managing SRAM for temporary storage of sequence values
- Using loops and registers for iterative calculations
========================================================
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  asm(
    "ldi r16, 0\n" //fib n-2
    "ldi r17, 1\n" //fib n-1
    "sts 0x0100, r16\n" //0x0100 has fib n-2
    "sts 0x0101, r17\n" //0x0101 has fib n-1

    "ldi r18, 0\n" //loop counter
    "ldi r19, 12\n" //loop total

    "1:" //loop label
    "call 2f\n" //call to fib function
    "inc r18\n" //inc loop counter
    "cp r18, r19\n"
    "brne 1b\n"
    "jmp 3f\n"

    "2:" //fib function
    "lds r20, 0x0101\n" //f n-1
    "lds r16, 0x0100\n" //f n-2
    "add r16, r20\n" //r16 now holds f 
    "sts 0x0100, r20\n"
    "sts 0x0101, r16\n"
    "ret\n"
    

    "3:"
    "nop\n"

  );

  Serial.println(_SFR_MEM8(0x0101));
  delay(1000);
}