#include <stdlib.h>
#include <stdio.h>

#include "chat.h"
#include "client.h"

int main(int argc, char **argv)
{
    int number;
    if(argc < 3)
    {
        printf("USES: ./client [0-4] [username]");
    }
    number = atoi(argv[1]);
    init_client(number, argv[2]);
    init();
    exit(EXIT_SUCCESS);
}
