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


void mov(int* a, int* b){
  a = b;
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
  for(;;){
    
  }
  halt();
  return 0;
}
