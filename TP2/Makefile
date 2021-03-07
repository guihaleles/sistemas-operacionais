CC=gcc
CFLAGS=-I.
DEPS = tp3virtual.h page_table.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp3virtual: tp3virtual.o page_table.o fifo.o rand.o
	$(CC) -o tp3virtual tp3virtual.o page_table.o fifo.o rand.o
		