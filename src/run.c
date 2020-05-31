//part of this solution taken from https://www.programmingsimplified.com/c-program-read-file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/run.h"
#include "../include/args.h"
#include "../include/process_array.h"
#include "../include/stats.h"



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
        p.time_queued = p.t;
        p.has_run = 0;
        p.load_time = p.kb/4 * 2;
        //printf("load time : %d\n", p.load_time);
        //printf("time,id,kb,runtime,remaining,time_queued\nREAD = %d,%d,%d,%d,%d,%d\n\n\n", p.t, p.id, p.kb, p.runtime, p.remaining, p.time_queued);
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
    print_array(p_A);
    for (int i=0; i<p_A.num; i++) {
        //TODO if there is spare memory then start running

        printf("%d, RUNNING, id=%d, remaining-time=%d\n", global_t, p_A.array[i].id, p_A.array[i].runtime);
        t += p_A.array[i].runtime;
        global_t += p_A.array[i].runtime;
        p_A.array[i].remaining -= p_A.array[i].runtime;
        printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_remaining(p_A)); //TODO will need to sort out proc waiting function
        p_A.array[i].end_time = global_t;
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);


    return;
}

//current_time, FINISHED, id=<process-id>, proc-remaining=<num_proc_left>\n

void rr(Process_Array p_A, int quantum) {
    int t = global_t;
    int i = 0;
    while(proc_remaining(p_A)) {
        //need to make sure process is ready to run
        if (p_A.array[i].t <= global_t) 
        {
            //print_array(p_A);
            printf("%d, RUNNING, id=%d, remaining-time=%d\n", global_t, p_A.array[i].id, p_A.array[i].remaining);
            //if we can finish the process before the quantum runs out
            if (p_A.array[i].remaining <= quantum) 
            {
                //quantum will be finished
                t += p_A.array[i].remaining;
                global_t += p_A.array[i].remaining;
                p_A.array[i].remaining = 0;
                p_A.array[i].has_run = 1;
                printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_remaining(p_A));
                p_A.array[i].end_time = global_t;
                //otherwise we need to keep the process waiting for the rr to come around again
            } else 
            {
                t += quantum;
                global_t += quantum;
                p_A.array[i].remaining -= quantum;
                p_A.array[i].time_queued = global_t;
                p_A.array[i].has_run = 1;
            }
        }
        
       
        //need to go back to start of array if there are still processes to be run
        // if (i == p_A.num-1) {
        //     i=0;
        // } else
        // {
        //     i++;
        // }
        i = next_proc(p_A);
        //printf("\ni : %d\n", i);

    }

    return;
}

