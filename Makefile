CC=gcc

CFLAGS=-g3 -O0

all: crc32

crc32: crc32.c Makefile
	$(CC) $(CFLAGS) testcrc.c adler.c crc32.c -o testcrc 

clean: 
	rm -f testcrc
