#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHUNK 8
#define LINESIZE 32
#define INSTRSIZE 32

// OPCODE
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

#define FIRST_ARG_MASK ( 0x3FFF << 14)
#define SECOND_ARG_MASK ( 0x3FFF << 0)

#define GET_FIRST(x)				\
  (x & FIRST_ARG_MASK ) >> 14

#define GET_SECOND(x)				\
  (x & SECOND_ARG_MASK) >> 0

#define OPCODE(x)                               \
  x << 27

#define IS(x, opcode)					\
  (x & OPCODE(opcode)) == OPCODE(opcode) ? 1 : 0

int* instructions;

void ProgName(char* name);
char** run(char* progName);
char** fetch(FILE* fd);
