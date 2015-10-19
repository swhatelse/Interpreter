#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include"VM.h"

#define CHUNK 8 // Size of the buffer to read the program name
#define LINESIZE 32

// Isolate the first argument from a binary instruction
#define FIRST_ARG_MASK ( 0x3FFF << (INSTRSIZE - OPCODESIZE) / 2)
// Isolate the second argument from a binary instruction
#define SECOND_ARG_MASK ( 0x3FFF << 0)

// Extract the first argument from a binary instruction
#define GET_FIRST(x)				\
  (x & FIRST_ARG_MASK ) >> (INSTRSIZE - OPCODESIZE) / 2

// Extract the second argument from a binary instruction
#define GET_SECOND(x)				\
  (x & SECOND_ARG_MASK) >> 0

// Place the opcode at the end of the instruction.
#define OPCODE(x)                               \
  x << INSTRSIZE - OPCODESIZE

// Isolate the opcode
#define GET_OPCODE(x)				\
  x & (0b1111 << INSTRSIZE - OPCODESIZE)

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
