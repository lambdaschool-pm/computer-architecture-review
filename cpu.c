#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

//make helper function to make sure address is in range
unsigned char cpu_ram_read(CPU *cpu, unsigned char address)
{
  return cpu->ram[address];
}

unsigned char cpu_ram_write(CPU *cpu, unsigned char address, unsigned char value)
{
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(CPU *cpu, char *filename)
{
  int address = 0;
  /*
  const int DATA_LEN = 6;
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };



  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }
  */
  // TODO: Replace this with something less hard-coded

  // get a pointer to the filename
	FILE *fp;
	char line[2000];

	// you are going to open the file using fopen()
	if((fp = fopen(filename, "r")) == NULL){
		// something wrong so we tell the user
		fprintf(stderr, "We can not open the %s\n", filename);
		exit(2);
	}
	// loop through the file reading the contents using fgets
	while(fgets(line, sizeof line, fp) != NULL){
		char *endchar;

		unsigned char opcode = strtol(line, &endchar, 2);

		// ignore empty lines
		if(endchar == line) {
			continue;
		}

    cpu->ram[address++] = opcode;
	}
}

/**
 * ALU
 */
void alu(CPU *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    case ALU_ADD:
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(CPU *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);

    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);

    printf("TRACE: %02x: %02x\n", cpu->pc, IR);

    switch(IR) {
      case ADD:
        cpu->reg[operandA] += cpu->reg[operandB];
        break;

      case HLT:
        running = 0;
        break;

      case LDI:
        cpu->reg[operandA] = operandB;
        break;

      case MUL:
        printf(" I am here %d %d \n", operandA, operandB);
        cpu->reg[operandA] *= cpu->reg[operandB];
        break;

      case PRN:
        printf("%d\n", cpu->reg[operandA]);
        break;

      default:
        printf("unknown instruction at %02x: %02x\n", cpu->pc, IR);
        exit(2);
    }

    // right shift it 6 places
    cpu->pc += (IR >> 6) + 1;

  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(CPU *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  // TODO: Zero registers and RAM
}
