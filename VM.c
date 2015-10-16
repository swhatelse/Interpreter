#include"VM.h"
#include<getopt.h>

int memSize = 1024;
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

void br(int x){
  R17 = R16;
  R16 = x;
}

void brlt(int x, int val){
  if(R[0] < val){
    R17 = R16;
    R16 = x;
  }
  else{
    R16++;
  }
}

void brgt(int x, int val){
 if(R[0] > val){
    R17 = R16;
    R16 = x;
  }
  else{
    R16++;
  }
}

void breq(int x, int val){
 if(R[0] == val){
    R17 = R16;
    R16 = x;
  }
  else{
    R16++;
  }
}

void brne(int x, int val){
 if(R[0] != val){
    R17 = R16;
    R16 = x;
  }
  else{
    R16++;
  }
}

void boot(){
  printf("Booting\n");
  
  memory = malloc(memSize * 1024);
  beginOfMem = memory + 0x1000;
  pageTableSize = (memSize - 0x1000) / PAGESIZE;
  pageTable = malloc(pageTableSize);
  printf("Available memory : %d\n", memSize);
}

void halt(){
  printf("Halting now!\n");
  turnOff = 1;

  free(memory);
  free(pageTable);
}
