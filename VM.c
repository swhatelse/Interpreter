#include"VM.h"

#define NBREGS 15
#define BUFSIZE 8
#define MEMSIZE 128

#define SHELL()                                 \
  printf("\033[32;1mIn the matrix ~/ $ \033[0m")

char RAM[MEMSIZE];

void movv(int x, int y){
  R[x] = y;
  (*R16)++;
}

void movr(int x, int y){
  R[x] = R[y];
  (*R16)++;
}

void movrp(int x, int y){
  R[x] = R[R[y]];
  (*R16)++;
}

void movpr(int x, int y){
  R[R[x]] = R[y];
  (*R16)++;
}

void add(int x, int y){
  R[x] += R[y];
  (*R16)++;
}

void mul(int x, int y){
  R[x] = R[x] * R[y]; 
  (*R16)++;
}

void sub(int x, int y){
  R[x] -= R[y];
  (*R16)++;
}

void divide(int x, int y){
  R[x] = R[x] / R[y]; 
  (*R16)++;
}

void br(int x){
  *R17 = *R16;
  *R16 = x;
}

void brlt(int x, int val){
  if(R[0] < val){
    *R17 = *R16;
    *R16 = x;
  }
  else{
    (*R16)++;
  }
}

void brgt(int x, int val){
 if(R[0] > val){
    *R17 = *R16;
    *R16 = x;
  }
  else{
    (*R16)++;
  }
}

void breq(int x, int val){
 if(R[0] == val){
    *R17 = *R16;
    *R16 = x;
  }
  else{
    (*R16)++;
  }
}

void brne(int x, int val){
 if(R[0] != val){
    *R17 = *R16;
    *R16 = x;
  }
  else{
    (*R16)++;
  }
}

void boot(){
  printf("Booting\n");
  /* for( int i = 0; i < 15; i++){ */
  /*   R[i] = malloc(sizeof(int));  */
  /* } */

  R15 = malloc(sizeof(int));
  R16 = malloc(sizeof(int));
  R17 = malloc(sizeof(int));
  R18 = malloc(sizeof(int));
  R19 = malloc(sizeof(int));
  R20 = malloc(sizeof(int));
  R21 = malloc(sizeof(int));

  /* __asm__("JMP 0x1000"); */
}

void halt(){
  printf("Halting now!\n");
  /* for( int i = 0; i < 15; i++){ */
  /*   free(R[i]);  */
  /* } */

  free(R15);
  free(R16);
  free(R17);
  free(R18);
  free(R19);
  free(R20);
  free(R21);
}

int main(int argc, char** argv){
  boot();
  char* progName = malloc( sizeof( char ) * CHUNK );
  
  // Waiting for a programm
  SHELL();
  ProgName(progName);
  FILE* fd = fopen(progName, "r");
  // Read progamm
  int nbInstr = compile(fd);
  run();
  
  // Close programm
  fclose(fd);
  free( progName );

  halt();
  return 0;
}
