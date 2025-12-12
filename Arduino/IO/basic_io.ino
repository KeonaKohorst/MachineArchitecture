/*
========================================================
Course: COSC211
Lab: Lab 7
Author: Keona Gagnier
Filename: basic_io.ino
Date Created: March 18 2024
Last Modified: December 12 2025
========================================================

Description:
This Arduino sketch implements a 24-bit counter using inline AVR
assembly. The counter is constructed using three nested loop
registers, each ranging from 1 to 255, effectively simulating a
triple-nested for loop.

Each complete iteration of the counter performs:
256 × 256 × 256 = 16,777,216 loop iterations.

When the outermost (most significant) loop register rolls over,
a separate display counter is incremented. This display counter
is written to PORTD to visually display the counter value on the
output pins. Due to the large number of iterations per increment,
the display updates approximately once every 6 seconds.

Before writing to the PORT register, the Data Direction Register
(DDRD) is set to 255 to configure all pins on PORTD as outputs.
The ST instruction is used to write values to both the DDR and
PORT registers.

The loop() function contains all assembly logic and runs
continuously, while the setup() function is unused. This exercise
reinforces:
- Implementing multi-level loop logic in AVR assembly
- Using register rollover to detect loop completion
- Writing to I/O registers using pointers and the ST instruction
- Understanding timing effects of large instruction counts
========================================================
*/


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t *ddr = &DDRD;
  uint8_t *port = &PORTD;

  asm volatile(
    "ldi r16, 1\n"         //first loop counter
    "ldi r17, 1\n"         //second loop counter
    "ldi r18, 1\n"         //third loop counter
    "ldi r19, 255\n"       //used to set DDR
    "st %a[ddr], r19\n"    //setting DDR to all output
    "ldi r19, 0\n"         //binary display counter
    
    "1:" //increment binary display counter
    "st %a[port], r19\n"
    "inc r19\n"
   
    "2:"//increment r16
    "inc r16\n"
    "tst r16\n"
    "breq 3f\n"
    "jmp 2b\n"
    
    "3:" //increment r17, reset r16
    "inc r17\n"
    "ldi r16, 1\n"
    "tst r17\n"
    "breq 4f\n"
    "jmp 2b\n"
    
    "4:" //increment r18, reset r17
    "inc r18\n"
    "ldi r16, 1\n"
    "ldi r17, 1\n"
    "tst r18\n"
    "breq 5f\n"
    "jmp 3b\n"
    
    "5:"
    "ldi r16, 1\n"
    "ldi r17, 1\n"
    "ldi r18, 1\n"
    "jmp 1b"
    : :
    [ddr] "e" (ddr),
    [port] "e" (port)

  );



  //test code
  // asm volatile(
  //   "ldi r16, 255\n"
  //   "st %a[ddr], r16\n"
  //   "ldi r16, 125\n"
  //   "st %a[port], r16\n"
  //   : :
  //   [ddr] "e" (ddr),
  //   [port] "e" (port)

  // );
}
