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

char** loadProg(char* progName){
  FILE* fd;
  char** prog = malloc(sizeof(char*));
  fd = fopen(progName, "r");
  char ch;
  char* line = malloc( sizeof( char ) * CHUNK );;
  int size = 0;
  int offset = 0;
  
  while( EOF != ( ch = fgetc( fd ) ) ){
    if(offset >= size ){
      line = ( char* ) realloc( line, CHUNK + offset );
      size += CHUNK;
    }
    memcpy(line + offset, &ch, sizeof( char ) );
    offset++;
    // EOL
    if(ch == '\n'){
      printf("%s", line);
      offset = 0;
      size = 0;
    }
    
  }
  fclose(fd);
  free( line );
  return prog;
}

void run(char* progName){
  for(;;){
    
  }
}
