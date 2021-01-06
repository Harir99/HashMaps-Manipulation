CC=gcc 
CFLAGS=-g -lm -std=c99 -Wall -pedantic

all: hash.o htest1 htest2 htest3 htest4

htest1: htest1.c hash.o hash.h 
	$(CC) $(CFLAGS) htest1.c hash.o -o htest1

htest1.o: htest1.c htest1.o hash.h
	$(CC) $(CFLAGS) -c htest1.c hash.o -o htest2.o

htest2: htest2.c hash.o hash.h 
	$(CC) $(CFLAGS) htest2.c hash.o -o htest2

htest2.o: htest2.c htest2.o hash.h
	$(CC) $(CFLAGS) -c htest2.c hash.o -o htest2.o

htest3: htest3.c hash.o hash.h 
	$(CC) $(CFLAGS) htest3.c hash.o -o htest3

htest3.o: htest3.c htest3.o hash.h
	$(CC) $(CFLAGS) -c htest3.c hash.o -o htest3.o

htest4: htest4.c hash.o hash.h 
	$(CC) $(CFLAGS) htest4.c hash.o -o htest4

htest4.o: htest4.c htest4.o hash.h
	$(CC) $(CFLAGS) -c htest4.c hash.o -o htest4.o


hash: hash.c hash.h 
	$(CC) $(CFLAGS) hash.c -o hash

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c -o hash.o

clean:
	rm -f *.o htest1 htest2 htest3 htest4
