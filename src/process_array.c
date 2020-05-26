#include "../include/process_array.h"

int proc_waiting(int t, Process_Array p_A) 
{
    int count=0;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].t <= t && p_A.array[i].remaining > 0) 
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
            return 1;
        }
    }
    return 0;
}

//gives the next process in line that is waiting based on time queued and then lowest process id
int next_proc(Process_Array p_A) {
    int min_i = 1;
    for (int i=0; i<p_A.num; i++)
    {
        if (p_A.array[i].time_queued < p_A.array[min_i].time_queued && p_A.array[i].remaining > 0 && p_A.array[min_i].remaining > 0) 
        {
            min_i = i;
        } else if (p_A.array[i].time_queued == p_A.array[min_i].time_queued && p_A.array[i].remaining > 0 && p_A.array[min_i].remaining > 0)
        {
            if (p_A.array[i].id < p_A.array[min_i].id)
            {
                min_i = i;
            }
        }
    }

    return min_i;
}
