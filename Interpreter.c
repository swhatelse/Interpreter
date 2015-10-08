#include"Interpreter.h"

void ProgName(char* name){
  char ch;
  int size = 0;
  int offset = 0;
  while( EOF != ( ch = fgetc( stdin ) ) && ch != '\n' ){
    if(offset >= size ){
      name = ( char* ) realloc( name, CHUNK + offset );
      size += CHUNK;
    }
    memcpy(name + offset, &ch, sizeof( char ) );
    offset++;
  }
}

char** run(char* progName){
  FILE* fd;
  char** prog = malloc(sizeof(char*));
  fd = fopen(progName, "r");
  char ch;
  char* instruction = malloc( sizeof( char ) * CHUNK );;
  int size = 0;
  int offset = 0;
  
  while( EOF != ( ch = fgetc( fd ) ) ){
    if(offset >= size ){
      instruction = ( char* ) realloc( instruction, CHUNK + offset );
      size += CHUNK;
    }
    memcpy(instruction + offset, &ch, sizeof( char ) );
    offset++;
    // EOL
    if(ch == '\n'){
      printf("%s", instruction);
      offset = 0;
      size = 0;
    }
    
  }
  fclose(fd);
  free( instruction );
  return prog;
}

char** fetch(FILE* fd){
  char** prog = malloc(sizeof(char*));
  char ch;
  /* char* instruction = malloc( sizeof( char ) * CHUNK ); */
  int size = 0;
  int offset = 0;
  int nbInstruction = 0;
  *prog = malloc( sizeof( char ) * CHUNK );

  // First Version
  /* // Fill a line */
  /* while( EOF != ( ch = fgetc( fd ) ) ){ */
  /*   if(offset >= size ){ */
  /*     instruction = ( char* ) realloc( instruction, CHUNK + offset ); */
  /*     size += CHUNK; */
  /*   } */
  /*   memcpy(instruction + offset, &ch, sizeof( char ) ); */
  /*   offset++; */
  /*   // EOL */
  /*   if(ch == '\n'){ */
  /*     printf("%s", instruction); */
  /*     offset = 0; */
  /*     size = 0; */
  /*     nbInstruction++; */
  /*     prog = ( char* ) realloc( prog, nbInstruction * sizeof(char*) ); */
  /*     *(prog + nbInstruction) = malloc( sizeof( instruction ) ); */
  /*     memcpy( *(prog + nbInstruction), instruction, sizeof(instruction)); */
  /*   } */
    
  /* } */

  while( EOF != ( ch = fgetc( fd ) ) ){
    // Allocate memory by chunks
    if(offset >= size ){
      *(prog + nbInstruction) = ( char* ) realloc( *(prog + nbInstruction), CHUNK + offset );
      size += CHUNK;
    }
    memcpy(*(prog + nbInstruction) + offset, &ch, sizeof( char ) );
    offset++;

    // Newline = new instruction
    if(ch == '\n'){
      printf("%s", *(prog + nbInstruction));
      nbInstruction++;
      prog = realloc(prog, sizeof(char*) * (nbInstruction+1) );
    }
  }
    
  fclose(fd);
  /* free( instruction ); */
  return prog;
}


