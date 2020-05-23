#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/main.h"

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "error: not enought arguements!\n");
        exit(0);
    }

    char *filename = argv[2];

    
    return 0;
}