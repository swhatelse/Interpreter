CC=gcc
CFLAGS=-g -std=c99

VM: VM.c Interpreter.c
	$(CC) $(CFLAGS) -o $@ $^
