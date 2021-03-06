#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __MY_TIME__
    #include <time.h>
#endif


#define N 1000001
#define BITS 32
#define BUFF_SIZE 4096

char count_r[N];
unsigned int triplets[N];
int prime[(N - 1) / BITS + 1];
unsigned int buff[BUFF_SIZE];

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
    #ifdef __MY_TIME__
        clock_t begin = clock();
    #endif
    memset(&prime, -1, sizeof(prime));
    memset(&count_r, 0, sizeof(count_r));
    #ifdef __MY_TIME__
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "memsets: %f\n", time_spent);
    #endif

    //clear_bit(0);
    clear_bit(1);


    #ifdef __MY_TIME__
        begin = clock();
    #endif
        // Criba

        for (i = 3; i * i < N; i+=2)
        {
            if (get_bit(i))
            {
                for (j = i * i; j < N; j += 2*i)
                {
                    clear_bit(j);
                }
                
            }
            
        }
        

        // for (i = 3; i < N; i+=3)
        // {
        //     clear_bit(i);
        //     count_r[i] = -1;
        // }

        // for (i = 3; i < N; i+=4)
        // {
        //     count_r[i] = -1;
        // }

        // tots aquell que són primers encara hem de dir que són primers
        
        
    #ifdef __MY_TIME__
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "clear 3: %f\n", time_spent);
    #endif


    #ifdef __MY_TIME__
        begin = clock();
    #endif
    int primer_4;
    // Ningú pregunta per 1
    int k;

    for (i = 3; i < N; i+=2) // Els parells ja els mirem després
    {
        if (get_bit(i))
        {
            primer_4 = i%4;
                        // Consistentment Millor :)
            if (primer_4 == 3) // N'hi ha com 80 d'aquests...
            {
                for (j = i * 3; j < N; j += 2*i) // Brooo que estava mirant els parells també  A tots els llocs puc sudar dels parells i del 4k+3 Ara només vull iterar sobre els 4k+1 sabent que i és 3 mod 4
                {
                    count_r[j] = -1;
                }
            }
            else
            {
                if(primer_4 == 1){
                    for(j = i; j < N; j += 4*i){ // Els números 3 mod 4 tenen almenys 1 primer 3 mod 4 així que és la meitat dels que mirem, 1/4 de 1e6  A tots els llocs puc sudar dels parells i del 4k+3
                        
                        if (count_r[j] >= 0)
                        {
                            //clear_bit(j); // Només cal si no ha estat marcat per primer_4 == 3
                            count_r[j]++;
                        }
                    }
                }
            }

        }
    }
    
    
    #ifdef __MY_TIME__
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "sieve: %f\n", time_spent);
    #endif

    #ifdef __MY_TIME__
        begin = clock();
    #endif
    unsigned int number, count = 0;

    // Això s'ha de poder millorar, només ens hem de mirar numeros 1 mod 4 però per Amdhal això no em millora massa la velocitat...
    // 5 és el primer que té
    for (i = 5; i < N; i += 2) // Encara es pot podar més sudant del parells
    {
        triplets[i - 1] = count;
        if ( i%4 != 3 && (count_r[i] > 0))
        {
            count += (1 << ( count_r[i] - 1 )); // Puc estalviar-me el -1 si l'inicialitzo com a -1
        }
        triplets[i] = count;
    }
    triplets[N - 1] = triplets[N - 2];
    #ifdef __MY_TIME__
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "Triplets Calc: %f\n", time_spent);
    #endif

    #ifdef __MY_TIME__
        begin = clock();
    #endif
    i = 0;
    unsigned int buff[16];
    while (scanf("%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u", &buff[0], &buff[1], &buff[2], &buff[3], &buff[4], &buff[5], &buff[6], &buff[7], &buff[8],  &buff[9], &buff[10], &buff[11], &buff[12], &buff[13], &buff[14], &buff[15]) && buff[0] != 0 && buff[1] != 0 && buff[2] != 0 && buff[3] != 0 && buff[4] != 0 && buff[5] != 0 && buff[6] != 0 && buff[7] != 0 && buff[8] != 0 && buff[9] != 0 && buff[10] != 0 && buff[11] != 0 && buff[12] != 0 && buff[13] != 0 && buff[14] != 0 && buff[15] != 0) // Si num és parell llavors fer num - 1 perquè els parells no fageixen res
    {

        printf("%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n", triplets[buff[0]], triplets[buff[1]], triplets[buff[2]], triplets[buff[3]], triplets[buff[4]], triplets[buff[5]], triplets[buff[6]], triplets[buff[7]], triplets[buff[8]], triplets[buff[9]], triplets[buff[10]], triplets[buff[11]], triplets[buff[12]], triplets[buff[13]], triplets[buff[14]], triplets[buff[15]]);
        // if (small_number_buffer[0] == 0 || small_number_buffer[1] == 0 || small_number_buffer[2] == 0 || small_number_buffer[3])
        // {
        //     break;
        // }
        
    }

    
    if (buff[0] != 0)
    {
        printf("%u\n", triplets[buff[0]]);
        if (buff[1] != 0)
        {
            printf("%u\n", triplets[buff[1]]);
            if(buff[2] != 0)
            {
                printf("%u\n", triplets[buff[2]]);
                if (buff[3] != 0)
                {
                    printf("%u\n", triplets[buff[3]]);
                    if (buff[4] != 0)
                    {
                        printf("%u\n", triplets[buff[4]]);
                        if (buff[5] != 0)
                        {
                            printf("%u\n", triplets[buff[5]]);
                            if(buff[6] != 0)
                            {
                                printf("%u\n", triplets[buff[6]]);
                                if (buff[7] != 0)
                                {
                                    printf("%u\n", triplets[buff[7]]);
                                        if (buff[8] != 0)
                                        {
                                            printf("%u\n", triplets[buff[8]]);
                                            if (buff[9] != 0)
                                            {
                                                printf("%u\n", triplets[buff[9]]);
                                                if(buff[10] != 0)
                                                {
                                                    printf("%u\n", triplets[buff[10]]);
                                                    if (buff[11] != 0)
                                                    {
                                                        printf("%u\n", triplets[buff[11]]);
                                                        if (buff[12] != 0)
                                                        {
                                                            printf("%u\n", triplets[buff[12]]);
                                                            if (buff[13] != 0)
                                                            {
                                                                printf("%u\n", triplets[buff[13]]);
                                                                if(buff[14] != 0)
                                                                {
                                                                    printf("%u\n", triplets[buff[14]]);
                                                                    if (buff[15] != 0)
                                                                    {
                                                                        printf("%u\n", triplets[buff[15]]);
                                                                    }
                                                                    
                                                                }
                                                            }
                                                            
                                                        }
                                                    }
                                                    
                                                }
                                            }
                                            
                                        }
                                }
                                
                            }
                        }
                        
                    }
                }
                
            }
        }
        
    }




    /*
    int n;
    while ((n = read(1, &buff, sizeof(buff))) > 0)
    {
        printf("Hola %u\n", buff[21]);
    }*/
    #ifdef __MY_TIME__
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "IO: %f\n", time_spent);
    #endif
}