CC=gcc
flags=-Wall -Wpedantic -O3 -std=c99 -g

main: main.c
	$(CC) $(flags) main.c -o main.o

main_2: main_2.c
	$(CC) $(flags) main_2.c -o main_2.o

prime_divisors: main_2.c
	$(CC) $(flags) prime_divisors.c -o prime_divisors.o