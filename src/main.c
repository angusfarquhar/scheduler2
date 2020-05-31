#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/args.h"
#include "../include/process.h"
#include "../include/run.h"

//example input: $ ./scheduler -f processes.txt -a ff -s 200 -m p
int main(int argc, char ** argv)
{
    Args a;
    //handle the stdin
    for (int i=0; i<argc; i++)
    {
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

    fprintf(stderr, "\n-f : %s", a.filename);
    fprintf(stderr, "\n-a : %s", a.schedulingAlgorithm);
    fprintf(stderr, "\n-m : %s", a.memoryAllocation);
    fprintf(stderr, "\n-s : %s", a.memorySize);
    fprintf(stderr, "\n-q : %s\n\n", a.quantum);

    run(a);

    
    return 0;
}