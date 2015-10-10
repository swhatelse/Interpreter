#include"Interpreter.h"

int* instructions = NULL;

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

  /* while( EOF != ( ch = fgetc( fd ) ) ){ */
  /*   // Allocate memory by chunks */
  /*   if(offset >= size ){ */
  /*     *(prog + nbInstruction) = ( char* ) realloc( *(prog + nbInstruction), CHUNK + offset ); */
  /*     size += CHUNK; */
  /*   } */
  /*   memcpy(*(prog + nbInstruction) + offset, &ch, sizeof( char ) ); */
  /*   offset++; */

  /*   // Newline = new instruction */
  /*   if(ch == '\n'){ */
  /*     printf("%s", *(prog + nbInstruction)); */
  /*     nbInstruction++; */
  /*     prog = realloc(prog, sizeof(char*) * (nbInstruction+1) ); */
  /*   } */
  /* } */
  char instr[32];
  while(fgets(instr, sizeof(instr), fd)){
    instructions = realloc(instructions, (nbInstruction+1) * sizeof(int));
    if(instr[0] != '\n'){
      // Determines OPCODE
      // Arithmetic operations
      if(instr[0] == 'A' && instr[1] == 'D' && instr[2] == 'D'){
        instructions[nbInstruction] = OPCODE(ADD);
      }
      else if(instr[0] == 'S' && instr[1] == 'U' && instr[2] == 'B'){
        instructions[nbInstruction] = OPCODE(SUB);
      }
      else if(instr[0] == 'M' && instr[1] == 'U' && instr[2] == 'L'){
        instructions[nbInstruction] = OPCODE(MUL);
      }
      else if(instr[0] == 'D' && instr[1] == 'I' && instr[2] == 'V'){
        instructions[nbInstruction] = OPCODE(DIV);
      }
      // Transfert operations
      else if(instr[0] == 'M' && instr[1] == 'O' && instr[2] == 'V'){
        if(instr[4] == 'R'){
          if(1){
            instructions[nbInstruction] = OPCODE(MOVV);
          }
        }
        else if(1){
          instructions[nbInstruction] = OPCODE(MOVV);
        }
        else{
          // trapp
        }
      }
      // Branches
      else if(instr[0] == 'B' && instr[1] == 'R'){
        if(instr[2] == ' '){
          instructions[nbInstruction] = OPCODE(BR);
        }
        else if(instr[2] == 'L' && instr[3] == 'T'){
          instructions[nbInstruction] = OPCODE(BRLT);
        }
        else if(instr[2] == 'G' && instr[3] == 'T'){
          instructions[nbInstruction] = OPCODE(BRGT);
        }
        else if(instr[2] == 'E' && instr[3] == 'Q'){
          instructions[nbInstruction] = OPCODE(BREQ);
        }
        else if(instr[2] == 'N' && instr[3] == 'E'){
          instructions[nbInstruction] = OPCODE(BRNE);
        }
        else{
          // trapp
        }
      }
      nbInstruction++;
    }
  }

  for(int i = 0; i < nbInstruction; i++){
    if(IS(instructions[i], BRGT))
      printf("brgt\n");
    else if(IS(instructions[i], ADD))
      printf("add\n");
    else if(IS(instructions[i], MOVV))
      printf("mov\n");
  }
  
  /* free( instruction ); */
  return prog;
}
