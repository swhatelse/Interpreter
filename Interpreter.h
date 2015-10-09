#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHUNK 8
#define BR      0b10010000  // Unconditionnal branch
#define BRLT    0b10100000  // Cond less than
#define BRGT    0b11000000  // Cond greater than
#define BREQ    0b11100000  // Cond equals
#define BRNOT   0b11110000  // Cond not equals
#define ADD     0b01000000
#define SUB     0b01010000
#define MUL     0b01100000
#define DIV     0b01110000
#define MOVV    0b00100000  // mov reg, val
#define MOVR    0b00110000  // mov reg, reg
#define MOVRP   0b00010000  // mov reg, [reg]
#define MOVPR   0b10000000  // mov [reg], reg

void ProgName(char* name);
char** run(char* progName);
char** fetch(FILE* fd);
