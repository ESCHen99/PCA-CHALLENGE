#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define N 1000001
#define BITS 32
#define BUFF_SIZE 4096

char count_r[N];
unsigned int triplets[N];
int prime[(N - 1) / BITS + 1];
char buff[BUFF_SIZE];

void clear_bit(int i){
    unsigned short index = i/BITS;
    int mask = ~(1 << (i % BITS));
    prime[index] = prime[index] & mask;
}

unsigned char get_bit(int i){
    unsigned int res;
    unsigned short index = i/BITS;
    int mask = (1 << (i % BITS));
    res = prime[index] & mask;
    return (res != 0);
}

int main(){
    // Eratostenes
    int i, j;
    clock_t begin = clock();
    memset(&prime, -1, sizeof(prime));
    memset(&count_r, 0, sizeof(count_r));
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "memsets: %f\n", time_spent);

    clear_bit(0);
    clear_bit(1);

    begin = clock();
    int primer_4;
    for (i = 1; i < N; i+=2) // Els parells ja els mirem després
    {
        if (get_bit(i))
        {
            primer_4 = i%4;
            for (j = i; j < N; j+=i)
            {
                clear_bit(j);
                // Diria que tenir if és més ràpid
                if (primer_4 == 1 && count_r[j] >= 0)
                {
                    count_r[j]++;
                }
                //count_r[j] += ((i % 4 == 1) & (count_r[j] >= 0));
                if (primer_4 == 3)
                {
                    count_r[j] = -1;
                }
            }
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "sieve: %f\n", time_spent);

    begin = clock();
    unsigned int number, count = 0;
    for (i = 1; i < N; i += 2) // Encara es pot podar més sudant del parells
    {
        triplets[i - 1] = count;
        if ((count_r[i] > 0))
        {
            count += (1 << ( count_r[i] - 1 )); // Puc estalviar-me el -1 si l'inicialitzo com a -1
        }
        triplets[i] = count;
    }
    triplets[N - 1] = triplets[N - 2];
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "Triplets Calc: %f\n", time_spent);


    //triplets[i] = count;
 //   printf("%u \n", i);
    begin = clock();
    while (scanf("%u", &number) && number != 0) // Si num és parell llavors fer num - 1 perquè els parells no fageixen res
    {
        printf("%u\n", triplets[number]);
    }

    /*
    int n;
    while ((n = read(1, &buff, sizeof(buff))) > 0)
    {
        printf("Hola %u\n", buff[21]);
    }*/
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "IO: %f\n", time_spent);

}