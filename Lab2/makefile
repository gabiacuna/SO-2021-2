objs = main.c funciones.c
CFLAGS = -W -Wall -lncurses
prog = main
CC = gcc
#Esta regla compila el progra principal
all: 
	$(CC) -o $(prog) $(objs) $(CFLAGS)
	./$(prog)

valg:
	valgrind ./main

clean:
	rm -f $(prog)