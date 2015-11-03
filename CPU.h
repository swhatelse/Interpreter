#ifndef CPU_H 
#define CPU_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include"Interpreter.h"

/***************************** CPU **************************/
// OPCODE
// Size of the opcode is 4 bits and are strong weight bits.
#define BR      0b1001  // Unconditionnal branch
#define BRLT    0b1010  // Cond less than
#define BRGT    0b1100  // Cond greater than
#define BREQ    0b1110  // Cond equals
#define BRNE    0b1111  // Cond not equals
#define ADD     0b0100
#define SUB     0b0101
#define MUL     0b0110
#define DIV     0b0111
#define MOVV    0b0010  // mov reg, val
#define MOVR    0b0011  // mov reg, reg
#define MOVRP   0b0001  // mov reg, [reg]
#define MOVPR   0b1000  // mov [reg], reg

#define INSTRSIZE 32 // Size of an instruction
#define OPCODESIZE 4
#define NBREGS 15

char cpu_mode; // 0 for user mode 1 for kernel mode

int R[NBREGS]; // Generics registers. R0 is the accumalator.
int R15; // SP
int R16; // PC
int R17; // Link register
int R18; // Status register
int R19; // Page table
int R20; // IRQ
int R21; // Interrupt mask

// Branch
void br(int instr);
void brlt(int instr, int val); // Compare R[0] to val and branch if R[0] < val then branch to instruction instr
void brgt(int instr, int val); // Compare R[0] to val and branch if R[0] > val then branch to instruction instr
void breq(int instr, int val); // Compare R[0] to val and branch if R[0] == val then branch to instruction instr
void brne(int instr, int val); // Compare R[0] to val and branch if R[0] != val then branch to instruction instr

// Arithmetic operations
void add(int x, int y);
void sub(int x, int y);
void mul(int x, int y);
void divide(int x, int y);

// Transfert operations
void movv(int x, int y);
void movr(int x, int y);
void movrp(int x, int y);
void movpr(int x, int y);
void load(int reg, int addr); // Not implemented yet
void store(int reg, int addr); // Not implemented yet
#endif
