//part of this solution taken from https://www.programmingsimplified.com/c-program-read-file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/main.h"

typedef struct Process {
    int t;
    int id;
    int kb;
    int runtime;
} Process;



int read(char *filename)
{
    char ch;
    FILE *fp;
    Process p;

    fp = fopen(filename, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nThe contents of %s file are:\n", filename);
    fscanf(fp, "%d%d%d%d", &p.t, &p.id, &p.kb, &p.runtime);
    
    printf("\np.t = %d\n", p.t);
    printf("\np.id = %d\n", p.id);
    printf("\np.id = %d\n", p.kb);
    printf("\np.id = %d\n", p.runtime);

    fclose(fp);
    return 0;
}

