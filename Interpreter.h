#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include"VM.h"

#define CHUNK 8 // Size of the buffer to read the program name
#define LINESIZE 32
#define INSTRSIZE 32 // Size of an instruction

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

// Isolate the first argument from a binary instruction
#define FIRST_ARG_MASK ( 0x3FFF << 14)
// Isolate the second argument from a binary instruction
#define SECOND_ARG_MASK ( 0x3FFF << 0)

// Extract the first argument from a binary instruction
#define GET_FIRST(x)				\
  (x & FIRST_ARG_MASK ) >> 14

// Extract the second argument from a binary instruction
#define GET_SECOND(x)				\
  (x & SECOND_ARG_MASK) >> 0

// Place the opcode at the end of the instruction.
#define OPCODE(x)                               \
  x << 28

// Isolate the opcode
#define GET_OPCODE(x)				\
  x & (0b1111 << 28)

// Allow to know which kind of instruction is x by comparing it with an opcode
#define IS(x, opcode)				\
  x == OPCODE(opcode)

#define SHELL()                                 \
  printf("\033[32;1mIn the matrix ~/ $ \033[0m")

int* instructions;
int turnOff;

void ProgName(char** name);
int compile(FILE* fd);
void run();

#endif
