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
    print_array(p_A);
    fprintf(stderr, "\nglobal_t = %d\n\n", global_t);
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
    int min_i = 0;
    int i = 0;
    while (i<p_A.num)
    {
        fprintf(stderr, "\nmin_i start of loop = %d\n", min_i);
        if (p_A.array[i].remaining == 0) 
        {
            fprintf(stderr, "\np_A.array[%d] = %d\n\n", i, p_A.array[i].remaining);
            i++;
        }
        if (p_A.array[min_i].remaining == 0) 
        {
            fprintf(stderr, "\nmini p_A.array[%d] = %d\n\n", min_i, p_A.array[min_i].id);
            min_i++;
        }
        else
        {
            if (p_A.array[i].time_queued < p_A.array[min_i].time_queued) 
            {
                min_i = i;
            } else if (p_A.array[i].time_queued > p_A.array[min_i].time_queued)
            {
                ;
            } else
            {   
                //check if there is a process waiting that hasn't run
                if (p_A.array[i].has_run < p_A.array[min_i].has_run) 
                {
                    fprintf(stderr, "%d less than %d\n", i, min_i);
                    min_i = i;
                }
                if (p_A.array[i].id > p_A.array[min_i].id) 
                {
                    ;
                } else
                {
                    min_i = i;
                }
                
                
                
                
            }
            
            
                 
        } 
        i++;
        fprintf(stderr, "\ni : %d\n", i);
        
    }
    fprintf(stderr, "\nmin_i : %d\n", min_i);

    return min_i;
}

void print_array(Process_Array p_A) {
    fprintf(stderr, "\n[i]\tt\tid\tkb\truntime\trem\tt_q\thas_run\tend\tpages\n");
    for (int i=0; i<p_A.num; i++)
    {
        fprintf(stderr, "[%d]\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, p_A.array[i].t, p_A.array[i].id, p_A.array[i].kb, p_A.array[i].runtime, p_A.array[i].remaining, p_A.array[i].time_queued, p_A.array[i].has_run, p_A.array[i].end_time, p_A.array[i].pages);
    }
    fprintf(stderr, "\n");
}
