#ifndef VM_H 
#define VM_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Interpreter.h"

#define NBREGS 15

int R[NBREGS]; // Generics registers. R0 is the accumalator.
int* R15; // SP
int* R16; // PC
int* R17; // Link register
int* R18; // Status register
int* R19; // Page table
int* R20; // IRQ
int* R21; // Interrupt mask

void* memory; // RAM

// Branch
void br(int x);
void brlt(int x, int y);
void brgt(int x, int y);
void breq(int x, int y);
void brne(int x, int y);

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

#endif
