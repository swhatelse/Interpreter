#ifndef MEMORY_H 
#define MEMORY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include"Interpreter.h"

/*************************** Memory *************************/
#define PAGESIZE 4096
#define PAGECODESIZE 6 // Size of the page number in the bits field
#define PTSIZE 16 // Number of entry in the page table
#define PTESIZE 8
#define MAXPROGSIZE PAGESIZE * PTSIZE
#define ADDRSIZE 16
// Protection code
#define RD 0b1 
#define WR 0b10
#define EX 0b100

#define IS_VALID(x)                             \
  (x >> (PTESIZE - 1)) & 0b1

#define DECODE_PROTECTION(x)                    \
  x & (0b1 << (PTESIZE - 2))

#define DECODE_PAGENB(x)                        \
  x & 0b11111

#define GET_INDEX(addr)                         \
  addr & (0xfffff << 12)

#define GET_OFFSET(addr)                        \
  addr & 0xfff

typedef uint32_t address;

typedef char pte_t;

pte_t* pageTable;
char* frameTable; // Used to know if a physical page is already in use.
int frameTableSize;
void* memory; // RAM
int memSize; // Size of RAM
void* beginOfMem; // Address at boot

address getPhysicalAddress(address addr);
int askPage();
int askFrame();
void freePage(int number);
void freeFrame(int number);

#endif
