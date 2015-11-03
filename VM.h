#ifndef VM_H 
#define VM_H

#include"Interpreter.h"

#define RX memory + 0x0010
#define TX memory + 0x0014
#define STATUS memory + 0X0015

void boot();
void halt();

#endif
