#ifndef STATS_H
#define STATS_H

#include "../include/process.h"
#include "../include/process_array.h"

void print_throughput(Process_Array p_A);
int max_throughput(int *array, int num);
int min_throughput(int *array, int num);
int avg_throughput(int *array, int num);
void print_turnaround_time(Process_Array p_A);
void print_timeoverhead(Process_Array p_A);
float max_timeoverhead(Process_Array p_A);
float avg_timeoverhead(Process_Array p_A);

#endif