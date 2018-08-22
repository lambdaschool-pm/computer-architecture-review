#ifndef _CPU_H_
#define _CPU_H_

// cpu struct
typedef struct cpu {
  unsigned char pc;
  unsigned char reg[8];
  unsigned ram[256];
}CPU;

//ALU operations
enum alu_op {
  ALU_MUL,
  ALU_ADD
};

#define LDI 0b10000010
#define PRN 0b01000111
#define HLT 0b00000001
#define MUL 0b10100010
#define ADD 0b10100000


// function declarations
extern void cpu_load(CPU *cpu, char *filename);
extern void cpu_init(CPU *cpu);
extern void cpu_run(CPU *cpu);

#endif
