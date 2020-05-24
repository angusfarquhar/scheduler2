#include "../include/process_array.h"

int proc_remaining(int t, Process_Array p_A) 
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

