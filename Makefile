CC=gcc
flags=-Wall -Wpedantic -O0 -std=c99 -g -D __MY_TIME__

main: main.c
	$(CC) $(flags) main.c -o main

test: prime_divisors
	time ./prime_divisors < test.in > test.out
	colordiff test.out test_main.out

time: prime_divisors
	time ./prime_divisors < test.in > test.out -D

strace: prime_divisors
	strace -c ./prime_divisors < test.in > test.out

prime_divisors: prime_divisors.c
	$(CC) $(flags) prime_divisors.c -o prime_divisors

bit_wise_sieve: bit_wise_sieve.c
	$(CC) $(flags) bit_wise_sieve.c -o bit_wise_sieve

char_sieve: char_sieve.c
	$(CC) $(flags) char_sieve.c -o char_sieve


buffred: millor_scanf.c
	$(CC) $(flags) -D __BUFFERED__ millor_scanf.c -o millor_scanf_buffered


no_buffered: millor_scanf.c
	$(CC) $(flags) millor_scanf.c -o millor_scanf
clean:
	rm -rf main prime_divisors bit_wise_sieve char_sieve millor_scanf millor_scanf_buffered
