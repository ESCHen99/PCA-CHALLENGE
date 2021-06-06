#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000001

int count_r[N];
int count_n[N];
char prime[N];

int main(){
    // Eratostenes
    //printf("%u\n", alpha(2, 1000000));
    int i, j;
    memset(&prime, 1, sizeof(prime));
    memset(&count_r, 0, sizeof(count_r));
    memset(&count_n, 0, sizeof(count_n));


    prime[0] = 0;
    prime[1] = 0;


    for (i = 0; i < N; i++)
    {
        if (prime[i])
        {
            for (j = i; j < N; j+=i)
            {
                prime[j] = 0;
                if (i % 4 == 1)
                {
                    count_r[j]++;
                }
                if (i % 4 == 3)
                {
                    count_n[j]++;
                }
            }
        }
    }

    unsigned int number, count = 0;
    count = 0;
    for (i = 0; i < N; i++)
    {
        if (count_n[i] == 0 && i%2 != 0 && count_r[i] > 0)
        {
            count += (1 << ( count_r[i] - 1 ));
        }
        count_r[i] = count;
    }

    while (scanf("%u", &number) && number != 0)
    {
        printf("%u\n", count_r[number]);
    }

}