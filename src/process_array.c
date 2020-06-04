#include <stdio.h>
#include "../include/process_array.h"

#define TRUE 1
#define FALSE 0

extern int global_t;

int proc_waiting(int t, Process_Array p_A) 
{
    int count=0;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].time_queued <= t && p_A.array[i].remaining > 0) 
        {
            count++;
        }
    }
    return count;
}

int proc_remaining(Process_Array p_A) 
{
    int count=0;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].remaining > 0) 
        {
            count++;
        }
    }
    return count;
}

//gives the next process in line that is waiting based on time queued and then lowest process id
int next_proc(Process_Array p_A) {
    //print_array(p_A);
    //fprintf(stderr, "\nglobal_t = %d\n\n", global_t);
    //if there's only one remaining pick that
    if (proc_remaining(p_A) == 1) {
        for (int i=0; i<p_A.num; i++)
        {
            if (p_A.array[i].remaining > 0) 
            {
                fprintf(stderr, "proc remaining = 1\n");
                return i;
            }
        }
    }

    // find something that still has time remaining and is waiting for the first minimum
    int min = 0;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued <= global_t) {
            min = i;
        }
    }

    
    for (int i=0; i<p_A.num; i++)
    {   //check for anything with smaller time queued
        if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued < p_A.array[min].time_queued) {
            min = i;
            //if time queued equal check if one has run before
        } else if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued == p_A.array[min].time_queued)
        {
            if (p_A.array[i].has_run < p_A.array[min].has_run) {
                min = i;
            } else if (p_A.array[i].has_run == p_A.array[min].has_run) {
                if (p_A.array[i].id < p_A.array[min].id) {
                    min = i;
                }
            }
            
        }
    }

    return min;
}

int next_proc_shortest(Process_Array p_A) {
    //print_array(p_A);
    //fprintf(stderr, "\nglobal_t = %d\n\n", global_t);
    //if there's only one remaining pick that
    if (proc_remaining(p_A) == 1) {
        for (int i=0; i<p_A.num; i++)
        {
            if (p_A.array[i].remaining > 0) 
            {
                fprintf(stderr, "proc remaining = 1\n");
                return i;
            }
        }
    }

    // find something that still has time remaining and is waiting for the first minimum
    int min = 0;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued <= global_t) {
            min = i;
        }
    }

    
    for (int i=0; i<p_A.num; i++)
    {   //check for anything with smaller time queued
        if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued < p_A.array[min].time_queued) {
            min = i;
            //if time queued equal check if one has run before
        } else if (p_A.array[i].remaining > 0 && p_A.array[i].time_queued == p_A.array[min].time_queued)
        {
            if (p_A.array[i].has_run < p_A.array[min].has_run) {
                min = i;
            } else if (p_A.array[i].has_run == p_A.array[min].has_run) {
                if (p_A.array[i].runtime < p_A.array[min].runtime) {
                    min = i;
                }
            }
            
        }
    }

    return min;
}

void print_array(Process_Array p_A) {
    fprintf(stderr, "\n[i]\tt\tid\tkb\truntime\trem\tt_q\thas_run\tend\tpages\tmemstart\n");
    for (int i=0; i<p_A.num; i++)
    {
        fprintf(stderr, "[%d]\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, p_A.array[i].t, p_A.array[i].id, p_A.array[i].kb, p_A.array[i].runtime, p_A.array[i].remaining, p_A.array[i].time_queued, p_A.array[i].has_run, p_A.array[i].end_time, p_A.array[i].pages, p_A.array[i].mem_start);
    }
    fprintf(stderr, "\n");
}
