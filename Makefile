#CIUREA Robert-Mihai - 313CBb
build:
	gcc trie.c utils.c main.c -std=c99 -o tema3 -Wall -g

run:
	./tema3 data.in data.out

valgrind:
	valgrind --leak-check=full ./tema3 data.in data.out

clean:
	rm -rf tema3