CC=gcc
flags=-Wall -Wpedantic -O3 -std=c99 -g

main: main.c
	$(CC) $(flags) main.c -o main

prime_divisors: prime_divisors.c
	$(CC) $(flags) prime_divisors.c -o prime_divisors

clean:
	rm -rf main prime_divisors