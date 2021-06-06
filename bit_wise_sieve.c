#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000032/32
#define SIZE 1000000
#define BITS 32

int sieve[N];

void clear_bit(int i){
    unsigned short index = i/BITS;
    int mask = ~(1 << (i % BITS));
    sieve[index] = sieve[index] & mask;
}

unsigned char get_bit(int i){
    unsigned int res;
    unsigned short index = i/BITS;
    int mask = (1 << (i % BITS));
    res = sieve[index] & mask;
    return (res != 0);
}

int main(){
    memset(&sieve, -1, sizeof(sieve));
    int i, j;
    clear_bit(0);
    clear_bit(1);
    for (i = 1; i < SIZE; i+=2)
    {

        if (get_bit(i) == 1)
        {
            
            for (j = i; j < SIZE; j += i)
            {

                clear_bit(j);
               
            }
            
        }
        
    }
    
    // for (i = 0; i < 10000; i++)
    // {
    //     if (get_bit(i) == 1)
    //     {
    //         printf("%u\n", i);
    //     }
        
    // }
    
    
}