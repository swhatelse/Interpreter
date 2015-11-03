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

// Get the real address in order to apply some read, write 
// or execute action on it.
// access is either RD, RW, or EX.
// Returns a pointer or NULL if it fails.
void* accesPhysicalAddress(address virt, char access){
  void* realAddr = NULL;
  int addrInVirtRam = 0;
  int index = GET_INDEX(virt);
  int offset = GET_OFFSET(virt);
  
  if(DECODE_PROTECTION(pageTable[index]) == access){
    if(IS_VALID(pageTable[index])){
      addrInVirtRam = (int)(pageTable[index] & 0b11111) * 0x1000;
      addrInVirtRam = (int)(DECODE_PAGENB(pageTable[index])) * 0x1000;
      realAddr = beginOfMem + addrInVirtRam + offset;
    }
    else{
      // Page fault
    }
  }
  else{
    // Access denied
    // traps
  }
  return realAddr;
}

// Ask for a page
// Return the number of the page or -1 if there is no
// frame or no page available.
int askPage(){
  for(int i = 0; i < MAXPROGSIZE / PAGESIZE; i++){
    if(pageTable[i] == 0){
      pageTable[i] = askFrame();
      return i;
    }
  }
  return -1;
}

// Reserve a frame in memory
// Return the number of the frame or -1 if there is no
// frame available.
int askFrame(){
  for(int i = 0; i < frameTableSize; i++){
    if(frameTable[i] == 0){
      frameTable[i] = 1;
      return i;
    }
  }
  return -1;
}

void freePage(int number){
  pageTable[number] = 0;
  freeFrame(number);
}

void freeFrame(int number){
  frameTable[number] = 0;
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
