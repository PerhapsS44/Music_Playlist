CC=gcc
CFLAGS=-Wall -Wextra -std=c99
DEBUG=-g -ggdb -march=native
build: structuri.o main.o playlist.o
	$(CC) $(CFLAGS) $(DEBUG) structuri.o playlist.o main.o -o tema1
playlist.o:
	$(CC) $(CFLAGS) $(DEBUG) -c ./playlist.c
structuri.o:
	$(CC) $(CFLAGS) $(DEBUG) -c ./structuri.c
main.o:
		$(CC) $(CFLAGS) $(DEBUG) -c main.c

cb:
	make clean
	make build
run: 
	make clean
	make build
	./tema1 file.in file.out
	clear
	cat file.out

clean:
	rm *.o
	rm tema1
