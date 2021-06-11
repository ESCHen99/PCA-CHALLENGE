#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define __BUFFERED__

int len(int n){
    int res = n > 0;
    while (n > 0)
    {
        n /= 10;
        res += (n > 0);
    }
    return res;
}

int main(){
    clock_t begin, end;
    double time_spent;
    
    #ifndef __BUFFERED__
    fprintf(stderr, "This is not Buffered version\n");
    begin = clock();
    unsigned int number;
    while (scanf("%u", &number) && number != 0)
    {
        printf("%u\n", number);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "IO: %f\n", time_spent);
    #endif

    #ifdef __BUFFERED__
    fprintf(stderr, "This is the Buffered version\n");
    begin = clock();
    

    char buff[8];
    char write_buff[8+8];
    int n;
    int number = 0;
    int i, j, len_num, ant = 0, next;
    int fi = 0;
    while ( ( n = read(0, buff, sizeof(buff))) > 0 && fi == 0)
    {
        j = 0;
        ant = 0;
        for (i = 0; i < n && fi == 0; i++)
        {
            if(buff[i] - '0' >= 0 && buff[i] - '0' <= 9){
                //printf("buff[%u]: %u\n", i, buff[i] - '0');
                number = number * 10 + (buff[i] - '0');
            }
            else{
                if (number != 0)
                {
                    len_num = len(number);
                    next = ant + len_num;
                    for (j = next - 1; j >= ant; --j, number /= 10)
                    {
                        //printf("ant: %u j: %u\n", ant, j);
                        write_buff[j] = number % 10 + '0';
                    }
                    write_buff[next] = '\n';
                    ant = next + 1;
                    //printf("%u len: %u\n", number, len(number));
                    number = 0;
                }
                else
                {
                    fi = 1;
                }
  
                
            }   
        }
        
        write(1, write_buff, ant);
    }

    

    
   

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "IO: %f\n", time_spent);
    #endif
}