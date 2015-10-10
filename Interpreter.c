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

int explode(const char* line, char** words){
  int nbWords = 0;
  int nbChars = 0;
  int i = 0;
  int beg = 0;

  while(line[i] != '\0'){
    if(line[i] == ' ' || line[i] == '\n'){
      words = realloc(words, sizeof(char*) * nbWords +1);
      *(words + nbWords) = realloc(*(words + nbWords), sizeof(char)*nbChars + 1);
      for(int j = beg, k = 0; j < i; j++, k++){
	*(*(words + nbWords)+k) = line[j];
      }
      *(*(words + nbWords)+nbChars) = '\0';
      nbWords++;
      nbChars = 0;
      beg = i + 1;
    }
    else{
      nbChars++;
    }
    i++;
  }

  return nbWords;
}

int translateToOpcode(char* word){
  int opcode = 0;
    if(word[0] == 'A' && word[1] == 'D' && word[2] == 'D'){
      opcode = OPCODE(ADD);
    }
    else if(word[0] == 'S' && word[1] == 'U' && word[2] == 'B'){
      opcode = OPCODE(SUB);
    }
    else if(word[0] == 'M' && word[1] == 'U' && word[2] == 'L'){
      opcode = OPCODE(MUL);
    }
    else if(word[0] == 'D' && word[1] == 'I' && word[2] == 'V'){
      opcode = OPCODE(DIV);
    }
    // Transfert operations
    else if(word[0] == 'M' && word[1] == 'O' && word[2] == 'V'){
      if(word[4] == 'R'){
	if(1){
	  opcode = OPCODE(MOVV);
	}
      }
      else if(1){
	opcode = OPCODE(MOVV);
      }
      else{
	// trapp
      }
    }
    // Branches
    else if(word[0] == 'B' && word[1] == 'R'){
      if(word[2] == ' '){
	opcode = OPCODE(BR);
      }
      else if(word[2] == 'L' && word[3] == 'T'){
	opcode = OPCODE(BRLT);
      }
      else if(word[2] == 'G' && word[3] == 'T'){
	opcode = OPCODE(BRGT);
      }
      else if(word[2] == 'E' && word[3] == 'Q'){
	opcode = OPCODE(BREQ);
      }
      else if(word[2] == 'N' && word[3] == 'E'){
	opcode = OPCODE(BRNE);
      }
      else{
	// trapp
      }
    }
  return opcode;
}

char** fetch(FILE* fd){
  char** prog = malloc(sizeof(char*));
  int nbInstruction = 0;
  int nbLines = 0;
  int nbWords = 0;
  char** line = NULL; 
  char instr[INSTRSIZE];
  char** words = malloc(sizeof(char*));
  
  while(fgets(instr, sizeof(instr), fd)){
    int nbWords = explode( instr, words);

    instructions = realloc(instructions, (nbInstruction+1) * sizeof(int));
    instructions[nbInstruction] = translateToOpcode(words[0]);
    // Determines OPCODE
    // Arithmetic operations
    /* if(words[0][0] == 'A' && words[0][1] == 'D' && words[0][2] == 'D'){ */
    /*   instructions[nbInstruction] = OPCODE(ADD); */
    /* } */
    /* else if(words[0][0] == 'S' && words[0][1] == 'U' && words[0][2] == 'B'){ */
    /*   instructions[nbInstruction] = OPCODE(SUB); */
    /* } */
    /* else if(words[0][0] == 'M' && words[0][1] == 'U' && words[0][2] == 'L'){ */
    /*   instructions[nbInstruction] = OPCODE(MUL); */
    /* } */
    /* else if(words[0][0] == 'D' && words[0][1] == 'I' && words[0][2] == 'V'){ */
    /*   instructions[nbInstruction] = OPCODE(DIV); */
    /* } */
    /* // Transfert operations */
    /* else if(words[0][0] == 'M' && words[0][1] == 'O' && words[0][2] == 'V'){ */
    /*   if(words[0][4] == 'R'){ */
    /* 	if(1){ */
    /* 	  instructions[nbInstruction] = OPCODE(MOVV); */
    /* 	} */
    /*   } */
    /*   else if(1){ */
    /* 	instructions[nbInstruction] = OPCODE(MOVV); */
    /*   } */
    /*   else{ */
    /* 	// trapp */
    /*   } */
    /* } */
    /* // Branches */
    /* else if(words[0][0] == 'B' && words[0][1] == 'R'){ */
    /*   if(words[0][2] == ' '){ */
    /* 	instructions[nbInstruction] = OPCODE(BR); */
    /*   } */
    /*   else if(words[0][2] == 'L' && words[0][3] == 'T'){ */
    /* 	instructions[nbInstruction] = OPCODE(BRLT); */
    /*   } */
    /*   else if(words[0][2] == 'G' && words[0][3] == 'T'){ */
    /* 	instructions[nbInstruction] = OPCODE(BRGT); */
    /*   } */
    /*   else if(words[0][2] == 'E' && words[0][3] == 'Q'){ */
    /* 	instructions[nbInstruction] = OPCODE(BREQ); */
    /*   } */
    /*   else if(words[0][2] == 'N' && words[0][3] == 'E'){ */
    /* 	instructions[nbInstruction] = OPCODE(BRNE); */
    /*   } */
    /*   else{ */
    /* 	// trapp */
    /*   } */
    /* } */
    nbInstruction++;
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
