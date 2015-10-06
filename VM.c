#include<stdio.h>

#define NBREGS 15

int* regs[NBREGS];
int* R15;
int* R16;
int* R17;
int* R18;
int* R19;
int* R20;
int* R21;


void movReg(int* a, int* b){
  a = b;
}

void movVal(int* a, int val){
  *a = b;
}


void add(int *regX, int *regY){
  *regX += *regY;
}

void mul(int *regX, int *regY){
  *regX = *regX * *regY; 
}

void sub(int *regX, int *regY){
  *regX -= *regY;
}

void div(int *regX, int *regY){
  *regX = *regX / *regY; 
}

void branch(){

}

void boot(){
  printf("Booting\n");
}

void halt(){
  printf("Halting now!");
}

int main(int argc, char** argv){
  boot();
  FILE* f;
  char* progName;
  for(;;){
    // Waiting for a program
    fopen(stdin);
    
  }
  halt();
  return 0;
}
