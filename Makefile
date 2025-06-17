CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o binary_tree.o

all: tree

tree: $(OBJ)
	$(CC) $(CFLAGS) -o tree $(OBJ)

main.o: main.c binary_tree.h
	$(CC) $(CFLAGS) -c main.c

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) $(CFLAGS) -c binary_tree.c

clean:
	rm -f *.o tree