#include"VM.h"

void boot(){
  printf("Booting\n");
  
  memory = malloc(memSize);
  beginOfMem = memory + 0x1000;
  frameTableSize = (memSize - 0x1000) / PAGESIZE;
  frameTable = malloc(frameTableSize);
}

void halt(){
  printf("Halting now!\n");
  turnOff = 1;
  free(memory);
  free(frameTable);
}
