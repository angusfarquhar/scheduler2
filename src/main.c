#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/main.h"

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
    Arguments arguments;
    char *arg;

    //handle the stdin
    for (int i=0; i<argc; i++) //TODO fix issue with null character at end of stdin
    {
        if (i == argc-1) {
            arg = argv[i];
            printf("\narg: %s", arg);
            
            
        }
        if (strcmp(argv[i], "-f") == 0) {
            arguments.filename = argv[i+1];
            
        } else if (strcmp(argv[i], "-a") == 0) {
            arguments.schedulingAlgorithm = argv[i+1];
            
        } else if (strcmp(argv[i], "-m") == 0) {
            arguments.memoryAllocation = argv[i+1];
            
        } else if (strcmp(argv[i], "-s") == 0) {
            arguments.memorySize = argv[i+1];
            
        } else if (strcmp(argv[i], "-q") == 0) {
            arguments.quantum = argv[i+1];
            
        }
        
    }

    printf("\n-f : %s", arguments.filename);
    printf("\n-a : %s", arguments.schedulingAlgorithm);
    printf("\n-m : %s", arguments.memoryAllocation);
    printf("\n-s : %s", arguments.memorySize);
    printf("\n-q : %s", arguments.quantum);

    if (!strcmp(arguments.quantum, "10")) {
        printf("WOW");
    }

    
    return 0;
}