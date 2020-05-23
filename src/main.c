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
    if (argc > 10)
    {
        fprintf(stderr, "error: not enought arguements!\n");
        exit(0);
    }
    
    //handle the stdin
    for (int i=0; i<argc; i++) 
    {
        if (strcmp(argv[i], "-f") == 0) {
            arguments.filename = argv[i+1];
        } else if (strcmp(argv[i], "-a") == 0) {
            arguments.schedulingAlgorithm = argv[i+1];
        } else if (strcmp(argv[i], "-s") == 0) {
            arguments.memoryAllocation = argv[i+1];
        } else if (strcmp(argv[i], "-m") == 0) {
            arguments.memorySize = argv[i+1];
        } else if (strcmp(argv[i], "-q") == 0) {
            arguments.quantum = argv[i+1];
        }
        
        
    }

    
    return 0;
}