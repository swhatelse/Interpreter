#include"VM.h"
#include<getopt.h>

int memSize = 2048;

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
  
  memory = malloc(memSize);

  R15 = malloc(sizeof(int));
  R16 = malloc(sizeof(int));
  R17 = malloc(sizeof(int));
  R18 = malloc(sizeof(int));
  R19 = malloc(sizeof(int));
  R20 = malloc(sizeof(int));
  R21 = malloc(sizeof(int));
}

void halt(){
  printf("Halting now!\n");
  turnOff = 1;
  free(R15);
  free(R16);
  free(R17);
  free(R18);
  free(R19);
  free(R20);
  free(R21);
}

/* int main(int argc, char** argv){ */
/*   int opt; */

/*   while( ( opt = getopt( argc, argv, "hm:" ) ) != -1 ){ */
/*     switch( opt ){ */
    
/*     case 'h': */
/*       fprintf(stderr, "Usage: %s [-h/m]\n \t\t- m : Memory size in bytes\n \t\t- h : help\n", */
/*               argv[0]); */
/*       exit(EXIT_FAILURE); */
/*       break; */
    
/*     case 'm': */
/*       memSize = atoi(optarg); */
/*       break; */
    
/*     default: */
/*       break; */
/*     } */
/*   } */
  
/*   boot(); */

/*   char* progName = NULL; */
  
/*   while(!turnOff){ */
/*     // Waiting for a programm */
/*     SHELL(); */

/*     ProgName(&progName); */

/*     if( strcmp(progName, "halt") > 0){ */
/*       FILE* fd = fopen(progName, "r"); */
    
/*       int nbInstr = compile(fd); */
/*       run(); */
    
/*       // Close programm */
/*       fclose(fd); */
/*     } */
/*     else{ */
/*       halt(); */
/*     } */
/*     free( progName ); */
/*     progName = NULL; */
/*   } */
/*   return 0; */
/* } */
