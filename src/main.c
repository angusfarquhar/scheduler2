#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/main.h"

//example input: $ ./scheduler -f processes.txt -a ff -s 200 -m p.
int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "error: not enought arguements!\n");
        exit(0);
    }

    char *filename = argv[2];

    printf("%s", filename);

    
    return 0;
}