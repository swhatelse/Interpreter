#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Interpreter.h"

#define NBREGS 15
#define BUFSIZE 8
#define MEMSIZE 128

#define SHELL()                                 \
  printf("\033[32;1mIn the matrix ~/ $ \033[0m")

int* R[NBREGS];
int* R15;
int* R16;
int* R17;
int* R18;
int* R19;
int* R20;
int* R21;

char RAM[MEMSIZE];

void movReg(int* a, int* b){
  a = b;
}

void movVal(int* a, int val){
  *a = val;
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

void divide(int *regX, int *regY){
  *regX = *regX / *regY; 
}

void branch(int *reg){

}

void boot(){
  printf("Booting\n");
  /* __asm__("JMP 0x1000"); */
}

void halt(){
  printf("Halting now!");
}

int main(int argc, char** argv){
  boot();
  char* progName = malloc( sizeof( char ) * CHUNK );
  
  // Waiting for a programm
  SHELL();
  ProgName(progName);
  FILE* fd = fopen(progName, "r");
  // Read progamm
  /* run(progName); */
  fetch(fd);
  
  // Close programm
  fclose(fd);
  free( progName );

  halt();
  return 0;
}
