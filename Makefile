CC=gcc
CFLAGS=-Wall -pedantic

tp4: main.c
	$(CC) -o tp4 main.c $(CFLAGS)
clean:
	rm -f tp4