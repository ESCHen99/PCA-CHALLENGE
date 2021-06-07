#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(){
    clock_t begin, end;
    double time_spent;
    
    #ifndef __BUFFERED__
    printf("This is not Buffered version\n");
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
    printf("This is the Buffered version\n");
    begin = clock();
    unsigned int buff[8];
    while (scanf("%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u", &buff[0], &buff[1], &buff[2], &buff[3], &buff[4], &buff[5], &buff[6], &buff[7]) && buff[0] != 0 && buff[1] != 0 && buff[2] != 0 && buff[3] != 0 && buff[4] != 0 && buff[5] != 0 && buff[6] != 0 && buff[7] != 0) // Si num és parell llavors fer num - 1 perquè els parells no fageixen res
    {

        printf("%u\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6], buff[7]);
        // if (small_number_buffer[0] == 0 || small_number_buffer[1] == 0 || small_number_buffer[2] == 0 || small_number_buffer[3])
        // {
        //     break;
        // }
        
    }

    if (buff[0] != 0)
    {
        printf("%u\n", buff[0]);
        if (buff[1] != 0)
        {
            printf("%u\n", buff[1]);
            if(buff[2] != 0)
            {
                printf("%u\n", buff[2]);
                if (buff[3] != 0)
                {
                    printf("%u\n", buff[3]);
                    if (buff[4] != 0)
                    {
                        printf("%u\n", buff[4]);
                        if (buff[5] != 0)
                        {
                            printf("%u\n", buff[5]);
                            if(buff[6] != 0)
                            {
                                printf("%u\n", buff[6]);
                                if (buff[7] != 0)
                                {
                                    printf("%u\n", buff[7]);
                                }
                                
                            }
                        }
                        
                    }
                }
                
            }
        }
        
    }
    

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "IO: %f\n", time_spent);
    #endif
}