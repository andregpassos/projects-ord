CC = gcc

all:
	$(CC) heapsort.c -o heapsort -fpermissive

clean:
	rm heapsort


