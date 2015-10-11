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

void run(){
  *R16 = 0;
  int current;
  int opcode = 0;
  int first_arg = 0;
  int second_arg = 0;

  for(int i= 0; i < 4; i++){
    // fetch
    current = instructions[*R16];

    // decode
    opcode = GET_OPCODE(current);
    switch (opcode){
    case OPCODE(BR):
      first_arg = GET_FIRST(current);
      printf("BR\n");
      br(first_arg);
      /* execute = br;  */
      break;
    case OPCODE(BRLT):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRLT\n");
      brlt(first_arg, second_arg);
      break;
    case OPCODE(BRGT):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRGT\n");
      brgt(first_arg, second_arg);
      break;
    case OPCODE(BREQ):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BREQ\n");
      breq(first_arg, second_arg);
      break;
    case OPCODE(BRNE):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRNE\n");
      brne(first_arg, second_arg);
      break;
    case OPCODE(ADD):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("ADD\n");
      add(first_arg, second_arg);
      break;
    case OPCODE(SUB):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("SUB\n");
      sub(first_arg, second_arg);
      break;
    case OPCODE(MUL):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MUL\n");
      mul(first_arg, second_arg);
      break;
    case OPCODE(DIV):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("DIV\n");
      div(first_arg, second_arg);
      break;
    case OPCODE(MOVV):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVV\n");
      movv(first_arg, second_arg);
      break;
    case OPCODE(MOVR):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVR\n");
      movr(first_arg, second_arg);
      break;
    case OPCODE(MOVRP):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVRP\n");
      movrp(first_arg, second_arg);
      break;
    case OPCODE(MOVPR):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVPR\n");
      movpr(first_arg, second_arg);
      break;
    }
    (*R16)++;
    // emulate
  }
}

int explode(const char* line, char** words){
  int nbWords = 0;
  int nbChars = 0;
  int i = 0;
  int beg = 0;

  while(line[i] != '\0'){
    // first count the number of characters of a word and then copy it
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

int translateToOpcode(char** words){
  int opcode = 0;
  if(words[0][0] == 'A' && words[0][1] == 'D' && words[0][2] == 'D'){
    opcode = OPCODE(ADD);
    opcode += strtol(&words[1][1], NULL, 10) << 14; 
    opcode += strtol(&words[2][1], NULL, 10);      
  }
  else if(words[0][0] == 'S' && words[0][1] == 'U' && words[0][2] == 'B'){
    opcode = OPCODE(SUB);
    opcode += strtol(&words[1][1], NULL, 10) << 14; 
    opcode += strtol(&words[2][1], NULL, 10);      
  }
  else if(words[0][0] == 'M' && words[0][1] == 'U' && words[0][2] == 'L'){
    opcode = OPCODE(MUL);
    opcode += strtol(&words[1][1], NULL, 10) << 14; 
    opcode += strtol(&words[2][1], NULL, 10);      
  }
  else if(words[0][0] == 'D' && words[0][1] == 'I' && words[0][2] == 'V'){
    opcode = OPCODE(DIV);
    opcode += strtol(&words[1][1], NULL, 10) << 14; 
    opcode += strtol(&words[2][1], NULL, 10);      
  }
  // Transfert operations
  else if(words[0][0] == 'M' && words[0][1] == 'O' && words[0][2] == 'V'){
    if(words[1][0] == 'R') {
      if(words[2][0] != 'R' && words[2][0] != '['){
	opcode = OPCODE(MOVV);
	opcode += strtol(&words[1][1], NULL, 10) << 14; 
	opcode += strtol(&words[2][0], NULL, 10);      
      }
      else if(words[2][0] == 'R'){
	opcode = OPCODE(MOVR);
	opcode += strtol(&words[1][1], NULL, 10) << 14; 
	opcode += strtol(&words[2][1], NULL, 10);      
      }
      else if(words[2][0] == '['){
	opcode = OPCODE(MOVRP);
	opcode += strtol(&words[1][1], NULL, 10) << 14; 
	opcode += strtol(&words[2][2], NULL, 10);      
      }
      else{
	// trap
      }
    }
    else if(words[1][0] == '['){
      opcode = OPCODE(MOVPR);
      opcode += strtol(&words[1][2], NULL, 10) << 14; 
      opcode += strtol(&words[2][1], NULL, 10);      
    }
    else{
      // trapp
    }
  }
  // Branches
  else if(words[0][0] == 'B' && words[0][1] == 'R'){
    if(strlen(words[0]) < 3){
      opcode = OPCODE(BR);
      opcode += strtol(&words[1][1], NULL, 10) << 14; 
    }
    else if(words[0][2] == 'L' && words[0][3] == 'T'){
      opcode = OPCODE(BRLT);
      opcode += strtol(&words[1][1], NULL, 10) << 14; 
      opcode += strtol(&words[2][0], NULL, 10);      
    }
    else if(words[0][2] == 'G' && words[0][3] == 'T'){
      opcode = OPCODE(BRGT);
      opcode += strtol(&words[1][1], NULL, 10) << 14; 
      opcode += strtol(&words[2][0], NULL, 10);      
    }
    else if(words[0][2] == 'E' && words[0][3] == 'Q'){
      opcode = OPCODE(BREQ);
      opcode += strtol(&words[1][1], NULL, 10) << 14; 
      opcode += strtol(&words[2][0], NULL, 10);      
    }
    else if(words[0][2] == 'N' && words[0][3] == 'E'){
      opcode = OPCODE(BRNE);
      opcode += strtol(&words[1][1], NULL, 10) << 14; 
      opcode += strtol(&words[2][0], NULL, 10);      
    }
    else{
      // trapp
    }
  }
  return opcode;
}

int compile(FILE* fd){
  int nbWords = 0;
  int nbInstruction = 0;
  char instr[INSTRSIZE];
  char** words = malloc(sizeof(char*));
  
  while(fgets(instr, INSTRSIZE, fd)){
    int nbWords = explode( instr, words);

    instructions = realloc(instructions, (nbInstruction+1) * sizeof(int));
    instructions[nbInstruction] = translateToOpcode(words);
    nbInstruction++;
  }

  for(int i = 0; i < nbInstruction; i++){
    if(IS(instructions[i], BRGT)){
      printf("brgt %d %d\n", GET_FIRST(instructions[i]), GET_SECOND(instructions[i]));
    }
    else if(IS(instructions[i], ADD)){
      printf("add %d %d\n", GET_FIRST(instructions[i]), GET_SECOND(instructions[i]));
    }
    else if(IS(instructions[i], MOVV)){
      printf("mov %d %d\n", GET_FIRST(instructions[i]), GET_SECOND(instructions[i]));
    }
    else if(IS(instructions[i], MOVPR)){
      printf("mov %d %d\n", GET_FIRST(instructions[i]), GET_SECOND(instructions[i]));
    }
  }
  free(words);
  return nbInstruction;
}
