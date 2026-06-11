CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

SRC=$(wildcard src/**/*.c src/*.c)
TESTS=$(wildcard tests/*.c)

<<<<<<< HEAD
# Filtramos src/main.c para que no choque con el main de los tests
SRC_NO_MAIN=$(filter-out src/main.c, $(SRC))

=======
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o bin/main

run:
	./bin/main

test:
	mkdir -p bin
<<<<<<< HEAD
	$(CC) $(CFLAGS) $(TESTS) $(SRC_NO_MAIN) -o bin/tests
	./bin/tests

clean:
	rm -rf bin/*
=======
	$(CC) $(CFLAGS) $(TESTS) $(SRC) -o bin/tests
	./bin/tests

clean:
	rm -rf bin/*
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
