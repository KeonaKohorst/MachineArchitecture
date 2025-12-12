Keona Gagnier

# Part 1: Computer Organization – Memory, ALU

### 1. What is the difference between assembly language and machine language?

	Assembly language is a human interpretable version of machine language, it is the lowest level form of programming before being in binary. Machine language is the language which computers are able to understand, aka binary.

### 2. In computer architecture, what does RISC stand for? Explain what the implications are if we say an architecture or language is RISC-based.

	Reduced Instruction Set Computing. It means the processor will perform less instructions and run faster than other processors which perform more instructions. 

### 3. Briefly explain the difference between a Von Neumann architecture and a Harvard Architecture.

	Von Neumann has a shared memory for both instructions and data, so you can only access one at a time. Harvard has separate memory for instructions and data, making them simultaneously accessible.

### 4. Based on what we’ve learnt about the AVR processor architecture, which classification (Von Neumann, Harvard, Modified Harvard) does AVR fall into?
	
	Modified Harvard Architecture.

### 5. Name the three major types of memory within the AVR architecture and provide a short description of what kind of information is stored in each memory.
	
	SRAM - data is stored here and registers use this memory.
	EEPROM - longer read/write lifespan, long term storage. 
	Flash - where instructions are stored and executed from, and data can be stored.

### 6. What memory address does the SRAM of an AVR processor start on? Note this is specifically the address of the start of SRAM, not the registers.
	
	0x0100 

### 7. If we wanted to store an arbitrary number value (say, 123) during the execution of our assembly code, which registers would we want to use for this?
	
	Any of the 32 general purpose registers, or just 16-32 if we need all programs to be able to access it.

### 8. In the AVR architecture, the ALU is logically connected to what other components of the Processor?
	
	The 32 General Purpose Registers, the data bus, and the status register.

### 9. If we performed an ADD instruction and saw that the carry bit in the status register was set to 1 afterwards, what does this imply about our ADD instruction?
	That there was an overflow, the result of the addition was larger than 255 and could not be stored back in the destination register.
	
### 10. When writing a SUBI instruction, how many bits are used for the constant (K) and how many are used for the register (Rd)?
	K - 8 bits
	Rd - 4 bits




# Part 2: Interpreting Assembly

```avrasm
.def regA = r16  //lower half n1
.def regB = r17 // upper half n1  (0x1F07 (7943))
.def regC = r18 //lower half n2 
.def regD = r19 //upper half n2   (0x012A (298))
.cseg
.org 0x00

ldi regA,0x07 (7) (lower half n1)
ldi regB,0x1F (31) (upper half n1)
ldi regC,0x2A (42) (lower half n2)
ldi regD,0x01 (1) (upper half n2)

add regA,regC
adc regB,regD
```

### After the ldi instructions:
```avrasm
regA = 7
regB = 31
regC = 42
regD = 1
```

### After the add instruction (adding lower bytes):
```avrasm
regA = 7 + 42

regA = 49
regB = 31
regC = 42
regD = 1
```


### After the adc instruction (adding upper bytes):
```avrasm
regB = 31 + 1 + 0

regA = 49 (0x31)
regB = 32 (0x20)
regC = 42
regD = 1
```

### Final 16-bit result:
0x2031 (8241 in decimal)
