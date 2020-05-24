#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/main.h"
#include "../include/read.h"

typedef struct Arguments {
    char* filename;
    char* schedulingAlgorithm;
    char* memoryAllocation;
    char* memorySize;
    char* quantum;
} Arguments;





//example input: $ ./scheduler -f processes.txt -a ff -s 200 -m p
int main(int argc, char ** argv)
{
    Arguments a;
    char *arg;

    //handle the stdin
    for (int i=0; i<argc; i++) //TODO fix issue with null character at end of stdin
    {
        if (i == argc-1) {
            arg = argv[i];
            printf("\narg: %s", arg);
            
            
        }
        if (strcmp(argv[i], "-f") == 0) {
            a.filename = argv[i+1];
            
        } else if (strcmp(argv[i], "-a") == 0) {
            a.schedulingAlgorithm = argv[i+1];
            
        } else if (strcmp(argv[i], "-m") == 0) {
            a.memoryAllocation = argv[i+1];
            
        } else if (strcmp(argv[i], "-s") == 0) {
            a.memorySize = argv[i+1];
            
        } else if (strcmp(argv[i], "-q") == 0) {
            a.quantum = argv[i+1];
            
        }
        
    }

    printf("\n-f : %s", a.filename);
    printf("\n-a : %s", a.schedulingAlgorithm);
    printf("\n-m : %s", a.memoryAllocation);
    printf("\n-s : %s", a.memorySize);
    printf("\n-q : %s", a.quantum);

    read(a.filename);

    
    return 0;
}