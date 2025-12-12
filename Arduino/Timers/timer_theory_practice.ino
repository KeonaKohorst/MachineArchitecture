/*
========================================================
Course: COSC211
Lab: Lab 8 Timer 1 Overflow Measurement
Author: Keona Gagnier
Filename: timer_theory_practice.ino
Date Created: March 25 2024
Last Modified: Dec 12 2025
========================================================

Description:
This Arduino sketch demonstrates configuring and using Timer1
on an AVR microcontroller to measure timer overflow intervals
using inline assembly.

In the setup() function, Timer1 control registers (TCCR1A and
TCCR1B) are configured using AVR assembly. TCCR1A is cleared,
and TCCR1B is set to use a selectable clock prescaler. An
overflow counter stored in SRAM at address 0x0120 is also
initialized to zero.

In the loop() function, the Timer1 Interrupt Flag Register
(TIFR1) is polled in assembly to detect timer overflow events.
When an overflow occurs, the flag is cleared manually, the
overflow counter is incremented, and execution continues.

The current elapsed time is printed to the Serial monitor using
millis(), allowing comparison between the measured overflow
intervals and theoretical timing values.

Extensive theoretical and experimental timing calculations are
included in comments for multiple prescaler values at both
16 MHz and 1 MHz clock speeds. These calculations demonstrate
close agreement between expected and measured timer behavior,
validating correct timer configuration.

This exercise reinforces:
- Direct timer configuration using AVR registers
- Polling hardware flags without interrupts
- Using SRAM to track overflow counts
- Comparing theoretical timing calculations with real hardware results
========================================================
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //Declare the timer config variable registers
  uint8_t* tccra = &TCCR1A;
  uint8_t* tccrb = &TCCR1B;

  //Use assembly to set register values
  asm volatile(
    "ldi r16, 0\n"
    "st %a[tccr_a], r16\n"  //Set TCCR1A to 0
    "sts 0x120, r16\n"      //Set overflow counter to 0
    "ldi r17, 5\n"          //Clock divider value
    "st %a[tccr_b], r17\n"  //Set TCCR1B to divider
    : :
    [tccr_a] "e" (tccra),
    [tccr_b] "e" (tccrb)
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t* tifr = &TIFR1;
  asm volatile(
    "1:"
    "ldi r17, 1\n"
    "ld r18, %a[tifrb]\n"
    "and r18, r17\n"
    "tst r18\n"
    "breq 1b\n"
    "ldi r20, 0\n"
    "st %a[tifrb], r20\n"
    "lds r19, 0x120\n"
    "inc r19\n"
    "sts 0x120, r19\n"
    : :
    [tifrb] "e" (tifr)

  );
  Serial.println(millis());
}
/*
---Calculations for 16MHz clock speed---

                   1          8           64           256           1024
Theoretical     0.0041      0.0328       0.2621       1.0487        4.1946

Actual          0.004       0.033        0.262        1.0483        4.1943


Below are my full calculations:

1 divider:
Theoretical: 
	16000000/(1 * 65535) = 244.1444 
	1 / 244.1444 = 0.0041 seconds
Actual:
	364 - 360 = 4 
	360 - 356 = 4 
	356 - 352 = 4 
	
	4 / 1000 = 0.004 seconds
	

8 divider:
Theoretical:
	16000000/(8*65535) = 30.5180
	1 / 30.5180 = 0.0328 seconds
Actual:
	688 - 655 = 33 
	655 - 622 = 33 
	622 - 589 = 33 
	
	33 / 1000 = 0.033 seconds

64 divider:
Theoretical:
	16000000/(64*65535) = 3.8148 
	1 / 3.8148 = 0.2621 seconds
Actual:
	1310 - 1048 = 262 
	1048 - 786 = 262 
	786 - 524 = 262 
	
	262 / 1000 = 0.262 seconds

256 divider:
Theoretical:
	16000000/(256*65535) = 0.9536
	1 / 0.9536 = 1.0487  seconds
Actual:
	5241 - 4193 = 1048 
	4193 - 3144 = 1049 
	3144 - 2096 = 1048 
	
	(1048 + 1049 + 1048) / 3 = 1048.3333 / 1000 = 1.0483 seconds

1024 divider:
Theoretical:
	16000000/(1024*65535) = 0.2384 
	1 / 0.2384 = 4.1946 seconds
Actual:
	20970 - 16776 = 4194 
	16776 - 12581 = 4195 
	12581 - 8387 = 4194 
	
	(4194 + 4195 + 4194)/3 = 4194.3333 / 1000 = 4.1943 seconds
	
	


---Calculations for 1MHz clock speed---

1024 divider:
Theoretical:
	1000000/(1024*65535) = 0.01490
	1 / 0.01490 = ***67.1141 seconds***
	
Actual:
	268419 - 201310 = 67109 
	201310 - 134201 = 67109 
	134201 - 67092 = 67109 
	
	67109 / 1000 = ***67.109 seconds***
	
Error:
67.1141 - 67.109 = ***0.0051 seconds***
*/