#include "CPU.h"

void movv(int x, int y){
  R[x] = y;
  R16++;
}

void movr(int x, int y){
  R[x] = R[y];
  R16++;
}

void movrp(int x, int y){
  R[x] = R[R[y]];
  R16++;
}

void movpr(int x, int y){
  R[R[x]] = R[y];
  R16++;
}

void add(int x, int y){
  R[x] += R[y];
  R16++;
}

void mul(int x, int y){
  R[x] = R[x] * R[y]; 
  R16++;
}

void sub(int x, int y){
  R[x] -= R[y];
  R16++;
}

void divide(int x, int y){
  R[x] = R[x] / R[y]; 
  R16++;
}

void br(int instr){
  R17 = R16;
  R16 = instr;
}

void brlt(int instr, int val){
  if(R[0] < val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void brgt(int instr, int val){
 if(R[0] > val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void breq(int instr, int val){
 if(R[0] == val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}

void brne(int instr, int val){
 if(R[0] != val){
    R17 = R16;
    R16 = instr;
  }
  else{
    R16++;
  }
}
