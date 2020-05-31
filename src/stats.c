#include <stdio.h>

#include "../include/stats.h"

extern int global_t;

void print_throughput(Process_Array p_A) {
    int stats[10] = {0};
    int avg=0;
    int min=0;
    int max=0;
    for (int i=0; i<p_A.num; i++) 
    {
        int bin = (p_A.array[i].end_time-1)/60;
        stats[bin] += 1; 
    }
    print_array(p_A);
    avg = avg_throughput(stats, 10);
    min = min_throughput(stats, 10);
    max = max_throughput(stats, 10);
    printf("Throughput %d, %d, %d\n", avg, min, max);

    return;
        
}

int max_throughput(int *array, int num) {
    int max = 0;
    for (int i=0; i<num; i++) 
    {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int min_throughput(int *array, int num) {
    int min = array[0];
    for (int i=0; i<num; i++) 
    {
        if (array[i] < min && array[i] != 0) {
            min = array[i];
        }
    }
    return min;
}

int avg_throughput(int *array, int num) {
    float total = 0;
    float count = 0;
    for (int i=0; i<num; i++) 
    {
        if (array[i] != 0 || i == 0 || i == 1) { //TODO fix this hacky avg bullshit
            total += array[i];
            fprintf(stderr, "total : %f\n", total);
            count++;
        }   
    }
    total = total/count;
    total = total + 0.9;
    return (int) total;
}

//Turnaround time: average time (in seconds, rounded up to an integer) 
//between the time when the process completed and when it arrived;
void print_turnaround_time(Process_Array p_A) {
    float total = 0;
    float count = 0;
    float turnaround = 0;
    for (int i=0; i<p_A.num; i++) 
    {
        turnaround = p_A.array[i].end_time - p_A.array[i].t;
        p_A.array[i].turnaround = turnaround;
        total += turnaround;
        count++;
    }
    total = total/count;
    total = total + 0.9;
    printf("Turnaround time %d\n", (int) total);
    return;
}

//Time overhead: maximum and average time overhead when running a process, 
//both rounded to the first two decimal points, where overhead is defined 
//as the turnaround time of the process divided by its job-time.
void print_timeoverhead(Process_Array p_A) {
    float turnaround;
    for (int i=0; i<p_A.num; i++) 
    {
        turnaround = p_A.array[i].end_time - p_A.array[i].t;
        p_A.array[i].time_overhead = turnaround / p_A.array[i].runtime;
        //printf("%f,%f,%d\n", p_A.array[i].time_overhead, turnaround, p_A.array[i].runtime);
    }
    float avg = avg_timeoverhead(p_A);
    //printf("avg = %f\n", avg);
    float max = max_timeoverhead(p_A);
    //printf("max = %f\n", max);

    printf("Time overhead %.2f %.2f\n", max, avg);

}

float max_timeoverhead(Process_Array p_A) {
    float max = 0;
    for (int i=0; i<p_A.num; i++) 
    {
        if (p_A.array[i].time_overhead > max) {
            max = p_A.array[i].time_overhead;
        }
    }
    return max;
}

float avg_timeoverhead(Process_Array p_A) {
    float total = 0;
    float count = 0;
    for (int i=0; i<p_A.num; i++) 
    {
        if (p_A.array[i].time_overhead != 0) {
            total += p_A.array[i].time_overhead;
            count++;
        }   
    }
    total = total/count;
    return total;
}

