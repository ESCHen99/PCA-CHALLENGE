#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define N 1000000

char prime[N];

int main(){
    // Eratostenes
    int i, j;
    memset(&prime, 1, sizeof(prime));

    prime[0] = 0;
    prime[1] = 0;

    for (i = 1; i < N; i+=2) // Els parells ja els mirem després
    {
        if (prime[i])
        {
            for (j = i; j < N; j+=i)
            {
                prime[j] = 0;
            }
        }
    }

    // for (i = 0; i < 10000; i++)
    // {
    //     if (prime[i] == 1)
    //     {
    //         printf("%u\n", i);
    //     }
        
    // }
}