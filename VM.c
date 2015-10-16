#include"VM.h"
#include<getopt.h>

int memSize = 2048;
void* beginOfMem = NULL;
void* memory = NULL;

void movv(int x, int y){
  R[x] = y;
  (R16)++;
}

void movr(int x, int y){
  R[x] = R[y];
  (R16)++;
}

void movrp(int x, int y){
  R[x] = R[R[y]];
  (R16)++;
}

void movpr(int x, int y){
  R[R[x]] = R[y];
  (R16)++;
}

void add(int x, int y){
  R[x] += R[y];
  (R16)++;
}

void mul(int x, int y){
  R[x] = R[x] * R[y]; 
  (R16)++;
}

void sub(int x, int y){
  R[x] -= R[y];
  (R16)++;
}

void divide(int x, int y){
  R[x] = R[x] / R[y]; 
  (R16)++;
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
    (R16)++;
  }
}

void brgt(int x, int val){
 if(R[0] > val){
    R17 = R16;
    R16 = x;
  }
  else{
    (R16)++;
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
  
  memory = malloc(memSize);
  beginOfMem = memory + 0x1000;
  pageTableSize = (memSize - 0x1000) / PAGESIZE;
  pageTable = malloc(pageTableSize);

  /* R15 = malloc(sizeof(int)); */
  /* R16 = malloc(sizeof(int)); */
  /* R17 = malloc(sizeof(int)); */
  /* R18 = malloc(sizeof(int)); */
  /* R19 = malloc(sizeof(int)); */
  /* R20 = malloc(sizeof(int)); */
  /* R21 = malloc(sizeof(int)); */
}

void halt(){
  printf("Halting now!\n");
  turnOff = 1;
  free(memory);
  /* free(R15); */
  /* free(R16); */
  /* free(R17); */
  /* free(R18); */
  /* free(R19); */
  /* free(R20); */
  /* free(R21); */
}
