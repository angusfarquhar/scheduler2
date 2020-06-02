//part of this solution taken from https://www.programmingsimplified.com/c-program-read-file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/run.h"
#include "../include/args.h"
#include "../include/process_array.h"
#include "../include/stats.h"
#include "../include/bitmap.h"



int global_t = 0;
Process_Array p_A;
Bitmap bitmap;

int run(Args a) 
{
    read(a.filename);
    //if unlimited memory
    if (strcmp(a.memoryAllocation, "u") == 0) {
        if (strcmp(a.schedulingAlgorithm, "ff") == 0) {
        ff(p_A);
        } else if (strcmp(a.schedulingAlgorithm, "rr") == 0)
        {
            rr(p_A, atoi(a.quantum));
        } else if (strcmp(a.schedulingAlgorithm, "cs") == 0) {
            //TODO my scheduling algorithm
            sjf_p(p_A, atoi(a.memorySize), 1000);
        }
    //if page swapping
    } else if (strcmp(a.memoryAllocation, "p") == 0) {
        if ((strcmp(a.schedulingAlgorithm, "ff") == 0)) {
            ff_p(p_A, atoi(a.memorySize));
        } else if (strcmp(a.schedulingAlgorithm, "rr") == 0) {
            rr_p(p_A, atoi(a.memorySize), atoi(a.quantum));
        }else if (strcmp(a.schedulingAlgorithm, "cs") == 0) {
            //TODO my scheduling algorithm
            sjf_p(p_A, atoi(a.memorySize), 1000);
        }
    }
    //if vm
    else{
        rr_vm(p_A, atoi(a.memorySize), atoi(a.quantum));
    }

    

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        p.pages = p.kb/4;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//current_time, RUNNING, id=<process-id>, remaining-time=<T_rem>, load-time=<T_load>, mem-usage=<mem_usage>%, mem-addresses=[<set_of_pages>]\n
void ff(Process_Array p_A) { //TODO handle the case when process isn't ready in time.
    int t = global_t;
    //print_array(p_A);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        i = next_proc(p_A);
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ff_p(Process_Array p_A, int memory) { //TODO handle the case when process isn't ready in time.
    int t = global_t;
    int pages = memory/4;
    //print_array(p_A);
    bitmap.num = pages;
    init_bitmap();
    fprintf(stderr, "pages = %d\n", bitmap.num);

    for (int i=0; i<p_A.num; i++) {
        //if proc not ready skip to that time
        if (p_A.array[i].time_queued > global_t) {
            global_t = p_A.array[i].time_queued;
        }
        //TODO if there is spare memory then start running
        if (room_for_process(p_A.array[i])) {
            //fprintf(stderr, "YES! THERE IS ROOM\n");
            //print_bitmap();
        } 
        //now process is running! print running stuff
        print_running(p_A.array[i]);
        print_mem_usage(p_A.array[i]);
        print_mem_addresses(p_A.array[i]);

        //adjust all the times after the process has run
        t += p_A.array[i].runtime;
        global_t += p_A.array[i].runtime;
        p_A.array[i].remaining -= p_A.array[i].runtime;
        
        //loading out of memory
        global_t += p_A.array[i].load_time;

        //evicted and finished printout
        printf("%d, EVICTED", global_t); //TODO will need to sort out proc waiting function
        print_mem_addresses(p_A.array[i]);
        printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_waiting(global_t, p_A));
        
        remove_process(p_A.array[i]);
        p_A.array[i].end_time = global_t;
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);


    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rr_p(Process_Array p_A, int memory, int quantum) {
    int t = global_t;
    int pages = memory/4;
    //print_array(p_A);
    bitmap.num = pages;
    init_bitmap();
    fprintf(stderr, "pages = %d\n", bitmap.num);
    int i = 0;
    while(proc_remaining(p_A)) {
        //need to make sure process is ready to run
        if (p_A.array[i].time_queued <= global_t) 
        {   
            //check if there's room in the bitmap
            if (room_for_process(p_A.array[i])) {
                //fprintf(stderr, "YES! THERE IS ROOM\n");
                //print_bitmap();
            } 
            //print running stuff
            print_running(p_A.array[i]);
            print_mem_usage(p_A.array[i]);
            print_mem_addresses(p_A.array[i]);    
            //if we can finish the process before the quantum runs out        
            if (p_A.array[i].remaining <= quantum) 
            {
                //quantum will be finished
                t += p_A.array[i].remaining;
                global_t += p_A.array[i].remaining;
                p_A.array[i].remaining = 0;
                p_A.array[i].has_run = 1;

                //loading out of memory
                global_t += p_A.array[i].load_time;
                printf("%d, EVICTED", global_t);
                print_mem_addresses(p_A.array[i]);
                printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_waiting(global_t, p_A));
                remove_process(p_A.array[i]);
                p_A.array[i].end_time = global_t;
                //otherwise we need to keep the process waiting for the rr to come around again
            } else 
            {
                t += quantum;
                global_t += quantum;
                p_A.array[i].remaining -= quantum;
                p_A.array[i].has_run = 1;
                
                //loading out of memory
                global_t += p_A.array[i].load_time;
                
                printf("%d, EVICTED", global_t);
                print_mem_addresses(p_A.array[i]);
                remove_process(p_A.array[i]);

                //process queued back up
                p_A.array[i].time_queued = global_t;

                

                
            }
        } else {
            global_t = p_A.array[i].time_queued;
        }
        i = next_proc(p_A);
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rr_vm(Process_Array p_A, int memory, int quantum) {
    int t = global_t;
    int pages = memory/4;
    //print_array(p_A);
    bitmap.num = pages;
    init_bitmap();
    fprintf(stderr, "pages = %d\n", bitmap.num);
    int i = 0;
    while(proc_remaining(p_A)) {
        //need to make sure process is ready to run
        if (p_A.array[i].t <= global_t) 
        {   
            //check if there's room in the bitmap
            if (room_for_vm(p_A.array[i])) {
                //fprintf(stderr, "YES! THERE IS ROOM\n");
                //print_bitmap();
            } 
            //print running stuff
            print_running(p_A.array[i]);
            print_mem_usage(p_A.array[i]);
            print_mem_addresses(p_A.array[i]);    
            //if we can finish the process before the quantum runs out        
            if (p_A.array[i].remaining <= quantum) 
            {
                //quantum will be finished
                t += p_A.array[i].remaining;
                global_t += p_A.array[i].remaining;
                p_A.array[i].remaining = 0;
                p_A.array[i].has_run = 1;

                //loading out of memory
                global_t += p_A.array[i].load_time;
                printf("%d, EVICTED", global_t);
                print_mem_addresses(p_A.array[i]);
                printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_waiting(global_t, p_A));
                remove_process_vm(p_A.array[i]);
                p_A.array[i].end_time = global_t;
                //otherwise we need to keep the process waiting for the rr to come around again
            } else 
            {
                t += quantum;
                global_t += quantum;
                p_A.array[i].remaining -= quantum;
                p_A.array[i].has_run = 1;
                
                //loading out of memory
                global_t += p_A.array[i].load_time;

                //don't evict if there's nothing else to swa
                if (i != next_proc(p_A)) {
                    printf("%d, EVICTED", global_t);
                    print_mem_addresses(p_A.array[i]);
                    remove_process_vm(p_A.array[i]);
                }
                

                //process queued back up
                p_A.array[i].time_queued = global_t;

                

                
            }
        }
        i = next_proc(p_A);
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sjf_p(Process_Array p_A, int memory, int quantum) {
    int t = global_t;
    int pages = memory/4;
    //print_array(p_A);
    bitmap.num = pages;
    init_bitmap();
    fprintf(stderr, "pages = %d\n", bitmap.num);
    int i = 0;
    while(proc_remaining(p_A)) {
        //need to make sure process is ready to run
        if (p_A.array[i].time_queued <= global_t) 
        {   
            //check if there's room in the bitmap
            if (room_for_process(p_A.array[i])) {
                fprintf(stderr, "YES! THERE IS ROOM\n");
                print_bitmap();
            } 
            //print running stuff
            print_running(p_A.array[i]);
            print_mem_usage(p_A.array[i]);
            print_mem_addresses(p_A.array[i]);    
            //if we can finish the process before the quantum runs out        
            if (p_A.array[i].remaining <= quantum) 
            {
                //quantum will be finished
                t += p_A.array[i].remaining;
                global_t += p_A.array[i].remaining;
                p_A.array[i].remaining = 0;
                p_A.array[i].has_run = 1;

                //loading out of memory
                global_t += p_A.array[i].load_time;
                printf("%d, EVICTED", global_t);
                print_mem_addresses(p_A.array[i]);
                printf("%d, FINISHED, id=%d, proc-remaining=%d\n", global_t, p_A.array[i].id, proc_waiting(global_t, p_A));
                remove_process(p_A.array[i]);
                p_A.array[i].end_time = global_t;
                //otherwise we need to keep the process waiting for the rr to come around again
            } else 
            {
                t += quantum;
                global_t += quantum;
                p_A.array[i].remaining -= quantum;
                p_A.array[i].has_run = 1;
                
                //loading out of memory
                global_t += p_A.array[i].load_time;
                
                printf("%d, EVICTED", global_t);
                print_mem_addresses(p_A.array[i]);
                remove_process(p_A.array[i]);

                //process queued back up
                p_A.array[i].time_queued = global_t;

                

                
            }
        } else {
            global_t = p_A.array[i].time_queued;
        }
        i = next_proc_shortest(p_A);
    }

    print_throughput(p_A);
    print_turnaround_time(p_A);
    print_timeoverhead(p_A);
    printf("Makespan %d\n", global_t);

    return;
}



void print_running(Process p) {
    printf("%d, RUNNING, id=%d, remaining-time=%d, load-time=%d", global_t, p.id, p.remaining, p.load_time);

}
