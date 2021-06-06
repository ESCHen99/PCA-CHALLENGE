#include <stdio.h>
#include <unistd.h>

#define NUM_SIZE 15
#define BUFF_SIZE 256

//char digit_buff[BUFF_SIZE];
//char number_array[NUM_SIZE];

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
 
int main(){

    //char digit;
    unsigned int i, j;
    unsigned int triplets = 0;
    
    unsigned int number = 0;
    //int n;

    // while(read(0, &digit, 1) && digit != '\n'){
    //     //printf("%u \n", digit - '0');
    //     number = (number + (digit - '0')) * 10;
    // }
    
    // number = number/10;
    while (scanf("%u", &number) && number != 0)
    {
        
        //printf("number: %d\n", number);
        triplets = 0;
        for (i = 1; i * i <= number * 2; i+=2)
        {
            for(j = 1; j * j + i * i <= number * 2 && j < i; j+=2){
                triplets += (gcd(j, i) == 1); 
            }
        }

        printf("%d\n", triplets);
    }
    

    
    
    
    return 0;
}
