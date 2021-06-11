#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef __MY_TIME__
    #include <time.h>
#endif


#define N 1000001
#define BITS 32
#define BUFF_SIZE 4096
#define index(i) i/BITS

char count_r[N];
unsigned int triplets[N];
int prime[(N - 1) / BITS + 1];
unsigned int buff[BUFF_SIZE];

static inline __attribute__((always_inline)) void clear_bit(int i){
    unsigned short index = i/BITS;
    int mask = ~(1 << (i % BITS));
    prime[index] = prime[index] & mask;
}

static inline __attribute__((always_inline)) unsigned char get_bit(int i){
    unsigned int res;
    unsigned short index = i/BITS;
    int mask = (1 << (i % BITS));
    res = prime[index] & mask;
    return (res != 0);
}

// L'entrada �s menor a 1e6 per tant la sortida t� max 6 d�gits
unsigned int len(unsigned int n){
    
    int res = 1;
    /*while (n > 0)
    {
        n /= 10;
        res += (n > 0);
    }
    return res;*/
	if(n <= 9) return 1;
    if(n >= 10 && n <=99) return 2;
    if(n >= 100 && n <= 999) return 3;
    if(n >= 1000 && n <= 9999) return 4;
    if(n >= 10000 && n <= 99999) return 5;
    if(n >= 100000 && n <= 999999) return 6; 
	while (n > 0)
    {
        n /= 10;
        res += (n > 0);
    }
    return res;
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
	// TODO: Check if over the array
    for (i = 3; i < N; i+=3)
    {
            clear_bit(i);
            count_r[i] = -1;
//			clear_bit(i + 3);
  //          count_r[i + 3] = -1;

    }
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
    for (i = 3; i < N; i+=2) // Els parells ja els mirem després
    {
        if (get_bit(i))
        {
            primer_4 = i%4;
                        // Consistentment Millor :)
            if (primer_4 == 3) // N'hi ha com 80 d'aquests...
            {
                for (j = i; j < N; j += 2*i) // Brooo que estava mirant els parells també  A tots els llocs puc sudar dels parells i del 4k+3
                {
                    if(j%3!=0){
                        clear_bit(j);
                        count_r[j] = -1;
                    }
                    
                }
            }
            else
            {
                if(primer_4 == 1){
                    for(j = i; j < N; j += 4*i){ // Els números 3 mod 4 tenen almenys 1 primer 3 mod 4 així que és la meitat dels que mirem, 1/4 de 1e6  A tots els llocs puc sudar dels parells i del 4k+3
                        
                        if (count_r[j] >= 0)
                        {
                            clear_bit(j); // Només cal si no ha estat marcat per primer_4 == 3
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
    unsigned int number = 0, count = 0;

    // Això s'ha de poder millorar, només ens hem de mirar numeros 1 mod 4 però per Amdhal això no em millora massa la velocitat...
    // 5 és el primer que té
    for (i = 5; i < N; i += 2) // Encara es pot podar més sudant del parells
    {
        triplets[i - 1] = count;
        if ((count_r[i] > 0))
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
    
    char buff[600000];
    char write_buff[600000 + 8]; // +8 pels q falten de l'anterior
    int n;
    int  fi = 0;
    int len_num, ant = 0, next;

    // Si queden ja estan comptats a dintre de number :)
    while((n = read(0, buff, sizeof(buff))) > 0 && fi == 0)
    {
        j = 0;
        ant = 0;
        for (i = 0; i < n && fi == 0; i++)
        {
            if(buff[i] - '0' >= 0 && buff[i] - '0' <= 9){
                number = number * 10 + (buff[i] - '0');
            }
            else{
                if (number != 0)
                {
                    number = triplets[number];
                    len_num = len(number);
                    next = ant + len_num;
                    for (j = next - 1; j >= ant; --j, number /= 10)
                    {
                        write_buff[j] = number % 10 + '0';
                    }
                    write_buff[next] = '\n';
					//next = sprintf(&write_buff[ant], "%u\n", number);
                    //ant += next;
					ant = next + 1;
                    number = 0;
                }
                else{
                    fi = 1;
                }
            }   
        }
        write(1, write_buff, ant);
    }

    #ifdef __MY_TIME__
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stderr, "IO: %f\n", time_spent);
    #endif
}
