CC=gcc
flags=-Wall -Wpedantic -O0 -std=c99 -g

main: main.c
	$(CC) $(flags) main.c -o main

test: prime_divisors
	time ./prime_divisors < test.in > test.out
	colordiff test.out test_main.out

time: prime_divisors
	time ./prime_divisors < test.in > test.out

strace: prime_divisors
	strace -c ./prime_divisors < test.in > test.out

prime_divisors: prime_divisors.c
	$(CC) $(flags) prime_divisors.c -o prime_divisors

bit_wise_sieve: bit_wise_sieve.c
	$(CC) $(flags) bit_wise_sieve.c -o bit_wise_sieve

char_sieve: char_sieve.c
	$(CC) $(flags) char_sieve.c -o char_sieve


clean:
	rm -rf main prime_divisors bit_wise_sieve char_sieve
