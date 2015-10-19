#include"VM.h"
#include<getopt.h>

int memSize = 1024 * 5;
void* beginOfMem = NULL;
void* memory = NULL;

void movv(int x, int y){
  R[x] = y;
  R16++;
}

void movr(int x, int y){
  R[x] = R[y];
  R16++;
}

void movrp(int x, int y){
  R[x] = R[R[y]];
  R16++;
}

void movpr(int x, int y){
  R[R[x]] = R[y];
  R16++;
}

void add(int x, int y){
  R[x] += R[y];
  R16++;
}

void mul(int x, int y){
  R[x] = R[x] * R[y]; 
  R16++;
}

void sub(int x, int y){
  R[x] -= R[y];
  R16++;
}

void divide(int x, int y){
  R[x] = R[x] / R[y]; 
  R16++;
}

void br(int instr){
  R17 = R16;
  R16 = instr;
}

void brlt(int instr, int val){
  if(R[0] < val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void brgt(int instr, int val){
 if(R[0] > val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void breq(int instr, int val){
 if(R[0] == val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void brne(int instr, int val){
 if(R[0] != val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

// Convert virtual address to physical addr
address getPhysicalAddress(address virt){
  int index = GET_INDEX(virt);
  int offset = GET_OFFSET(virt);
  address physical = (address)((pageTable[index] << (ADDRSIZE - PAGECODESIZE)) + offset);
  return physical;
}

// Ask for a page in physical memory
// Return the pointer to the begining 
// of the page
address getPhysicalPage(){
  address page = 0;
  for(int i = 0; i < frameTableSize; i++){
    if(frameTable[i] == 0){
      frameTable[i] = 1;
      page = i << (ADDRSIZE - PAGECODESIZE);
    }
  }
  return page;
}

address getVirtualPage(){
  address page = 0;
  for(int i = 0; i < MAXPROGSIZE / PAGESIZE; i++){
    if(pageTable[i]){
      pageTable[i] = getPhysicalPage();
    }
  }
  return page;
}

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
