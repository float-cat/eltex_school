#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_funcs.h"

#define MAX_STRING_SIZE (20)

int main(void)
{
    unsigned int a;
    unsigned int b;
    unsigned int result;
    char typeOperation = 0;
    char buffer[MAX_STRING_SIZE];
    while(1)
    {
        printf("1: Add, 2: Sub, 3: Multi, 4: Div, 0: Quit\n");
        fgets(buffer, MAX_STRING_SIZE, stdin);
        typeOperation = buffer[0];
        if(typeOperation == '0')
            exit(0);
        printf("Input argument 1\n");
        fgets(buffer, MAX_STRING_SIZE, stdin);
        a = atoi(buffer);
        printf("Input argument 2\n");
        fgets(buffer, MAX_STRING_SIZE, stdin);
        b = atoi(buffer);
        switch(typeOperation)
        {
            case '1': result = summBin(a, b, NULL);
                      printf("%d+%d=%d\n", a, b, result);
                      break;
            case '2': result = diffBin(a, b);
                      printf("%d-%d=%d\n", a, b, result);
                      break;
            case '3': result = multiBin(a, b);
                      printf("%d*%d=%d\n", a, b, result);
                      break;
            case '4': result = divBin(a, b);
                      printf("%d/%d=%d\n", a, b, result);
                      break;
        }
    }
    return 0;
}
