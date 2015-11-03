CC=gcc
CFLAGS=-g -std=c99

VM: VM.c Interpreter.c CPU.c memory.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f VM
