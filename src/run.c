//part of this solution taken from https://www.programmingsimplified.com/c-program-read-file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/run.h"
#include "../include/args.h"
#include "../include/process_array.h"


int global_t = 0;
Process_Array p_A;

int run(Args a) 
{
    read(a.filename);
    ff(p_A);

    return 0;
}

//read a file from input and create the process data structure
void read(char *filename)
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

    int i = 0;
    while(fscanf(fp, "%d%d%d%d", &p.t, &p.id, &p.kb, &p.runtime) == 4) {
        //assign file values to process struct
        p.remaining = p.runtime;
        p.complete = 0;
        printf("READ = %d,%d,%d,%d,%d,%d\n\n\n", p.t, p.id, p.kb, p.runtime, p.remaining, p.complete);
        //save in process_array and keep track of how many processes
        p_A.array[i] = p;
        p_A.num++;
        i++;
        
    }

    fclose(fp);
    return;
}


//current_time, RUNNING, id=<process-id>, remaining-time=<T_rem>, load-time=<T_load>, mem-usage=<mem_usage>%, mem-addresses=[<set_of_pages>]\n
void ff(Process_Array p_A) { //TODO handle the case when process isn't ready in time.
    int t = global_t;
    for (int i=0; i<p_A.num; i++) {
        printf("%d, RUNNING, id=%d, remaining-time=%d\n", global_t, p_A.array[i].id, p_A.array[i].runtime);
        t += p_A.array[i].runtime;
        global_t += p_A.array[i].runtime;
    }

    return;
}

