#include"Interpreter.h"

int* instructions = NULL;
int nbInstruction;
int turnOff = 0;

// Read a line from the command line to get the name of the program
// and store it into name. Name must be free'd at the end.
void ProgName(char** name){
  char ch;
  int size = 0;
  int offset = 0;
  while( EOF != ( ch = fgetc( stdin ) ) && ch != '\n' ){
    if(offset >= size ){
      *name = ( char* ) realloc( *name, CHUNK + offset );
      size += CHUNK;
    }
    *(*(name)+offset) = ch;
    offset++;    
  }
  if(offset >= size ){
    *name = ( char* ) realloc( *name, offset );
    size += CHUNK;
  }
  *(*(name)+offset) = '\0';
}

// Take instruction in input by using line and separate each words of the instruction
// in an array. words must be free'd at the end.
// Returns the number of words in the instruction written in the array.
int explode(const char* line, char*** words){
  int nbWords = 0;
  int nbChars = 0;
  int i = 0;
  int beg = 0;

  while(line[i] != '\0'){
    // first count the number of characters of a word and then copy it
    if(line[i] == ' ' || line[i] == '\n'){
      *words = realloc(*words, sizeof(char*) * (nbWords + 1));
      (*words)[nbWords] = realloc((*words)[nbWords], sizeof(char)*nbChars + 1);

      for(int j = beg, k = 0; j < i; j++, k++){
        (*words)[nbWords][k] = line[j];
      }
      (*words)[nbWords][nbChars] = '\0';
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

// Emulate the program previously compile by the function compile and stored 
// in the variable instruction. 
void run(){
  int current;
  int opcode = 0;
  int first_arg = 0;
  int second_arg = 0;

  for(*R16 = 0; *R16 < nbInstruction;){
    // fetch
    current = instructions[*R16];

    // decode
    opcode = GET_OPCODE(current);
    switch (opcode){
    case OPCODE(BR):
      first_arg = GET_FIRST(current);
      printf("BR %d\n", first_arg);
      br(first_arg);
      break;
    case OPCODE(BRLT):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRLT %d %d\n", first_arg, second_arg);
      brlt(first_arg, second_arg);
      break;
    case OPCODE(BRGT):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRGT %d %d\n", first_arg, second_arg);
      brgt(first_arg, second_arg);
      break;
    case OPCODE(BREQ):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BREQ %d %d\n", first_arg, second_arg);
      breq(first_arg, second_arg);
      break;
    case OPCODE(BRNE):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("BRNE %d %d\n", first_arg, second_arg);
      brne(first_arg, second_arg);
      break;
    case OPCODE(ADD):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("ADD %d %d\n", first_arg, second_arg);
      add(first_arg, second_arg);
      break;
    case OPCODE(SUB):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("SUB %d %d\n", first_arg, second_arg);
      sub(first_arg, second_arg);
      break;
    case OPCODE(MUL):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MUL %d %d\n", first_arg, second_arg);
      mul(first_arg, second_arg);
      break;
    case OPCODE(DIV):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("DIV %d %d\n", first_arg, second_arg);
      div(first_arg, second_arg);
      break;
    case OPCODE(MOVV):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVV %d %d\n", first_arg, second_arg);
      movv(first_arg, second_arg);
      break;
    case OPCODE(MOVR):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVR %d %d\n", first_arg, second_arg);
      movr(first_arg, second_arg);
      break;
    case OPCODE(MOVRP):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVRP %d %d\n", first_arg, second_arg);
      movrp(first_arg, second_arg);
      break;
    case OPCODE(MOVPR):
      first_arg = GET_FIRST(current);
      second_arg = GET_SECOND(current);
      printf("MOVPR %d %d\n", first_arg, second_arg);
      movpr(first_arg, second_arg);
      break;
    }
  }
  printf("Result = %d\n", R[0]);
}

// Convert the instruction store in words in opcode.
// Return the corresponding opcode.
// TODO manage traps when instruction does not exist.
int translateToBinary(char** words){
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

// Convert an assembly file fd in a set of binary instruction.
// fd must be opened and closed manually.
// Returns the number of instructions.
int compile(FILE* fd){
  int nbWords = 0;
  nbInstruction = 0;
  char instr[INSTRSIZE];
  char** words = malloc(sizeof(char*));
  
  while(fgets(instr, INSTRSIZE, fd)){
    int nbWords = explode( instr, &words);

    /* instructions = realloc(instructions, (nbInstruction+1) * sizeof(int)); */
    instructions = (int*) beginOfMem;
    instructions[nbInstruction] = translateToBinary(words);
    nbInstruction++;
  }

  free(words);
  return nbInstruction;
}

int main(int argc, char** argv){
  int opt;

  while( ( opt = getopt( argc, argv, "hm:" ) ) != -1 ){
    switch( opt ){
    case 'h':
      fprintf(stderr, "Usage: %s [-h/m]\n \t\t- m : Memory size in bytes\n \t\t- h : help\n",
              argv[0]);
      exit(EXIT_FAILURE);
      break;
    case 'm':
      memSize = atoi(optarg);
      break;    
    default:
      break;
    }
  }
  
  boot();

  char* progName = NULL;
  
  while(!turnOff){
    // Waiting for a programm
    SHELL();
    ProgName(&progName);

    if( strcmp(progName, "halt") > 0){
      FILE* fd = fopen(progName, "r");    
      int nbInstr = compile(fd);
      run();
    
      // Close programm
      fclose(fd);
    }
    else{
      halt();
    }
    free( progName );
    progName = NULL;
  }
  return 0;
}
