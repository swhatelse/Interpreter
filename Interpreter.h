#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHUNK 8

void ProgName(char* name);
char** run(char* progName);
char** fetch(FILE* fd);
