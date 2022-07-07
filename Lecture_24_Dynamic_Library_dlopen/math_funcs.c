#include "math_funcs.h"

int bitOfPos(unsigned int number, short pos)
{
    return 0 < (number & (1 << pos));
}

int setOfPos(unsigned int number, short pos, int i)
{
    if(i == 1)
        return number | (1 << pos);
    return number & ~(1 << pos);
}

unsigned int summBin(unsigned int a, unsigned int b, int *flag)
{
    int mem = 0;
    int ab, bb;
    unsigned int result = 0;
    if(flag != NULL)
        *flag = 0;
    for(int i = 0; i < 32; i++)
    {
        ab = bitOfPos(a, i);
        bb = bitOfPos(b, i);
        if(ab && bb && mem)
        {
            mem = 1;
            result = setOfPos(result, i, 1);
            if(flag != NULL && i > 30)
                *flag = 1;
        }
        else if((ab && bb) || (ab && mem) || (bb && mem))
        {
            mem = 1;
            result = setOfPos(result, i, 0);
        }
        else if(mem || ab || bb)
        {
            result = setOfPos(result, i, 1);
            mem = 0;
            if(flag != NULL && i > 30)
                *flag = 1;
        }
        else
        {
            result = setOfPos(result, i, 0);
            mem = 0;
        }
    }
    return result;
}

unsigned int diffBin(unsigned int a, unsigned int b)
{
    return summBin(a, ~b + 1, NULL);
}

unsigned int multiBin(unsigned int a, unsigned int b)
{
    int i, flag = 0;
    int result = 0, tmp = a << 16;
    for(i = 0; i < 16; i++)
    {
        if(bitOfPos(b, i))
            result = summBin(result, tmp, &flag);
        result >>= 1;
        if(flag)
        {
            result |= 1 << 31;
            flag = 0;
        }
    }
    return result;
}

unsigned int divBin(unsigned int a, unsigned int b)
{
    int i;
    unsigned int divtmp = 0;
    int result = 0;
    for(i = 31; i >= 0; i--)
    {
        divtmp <<= 1;
        divtmp |= bitOfPos(a, i);
        if(diffBin(divtmp, b) > divtmp)
            continue;
        divtmp = diffBin(divtmp, b);
        result = setOfPos(result, i, 1);
    }
    return result;
}

void decToBin(unsigned int d)
{
    int i;
    unsigned int border = floor(log(d)/log(2));
    printf("%d\n", border);
    printf("[");
    for(i = border; i >= 0; i--)
        printf("%d", bitOfPos(d, i));
    printf("]\n");
}
