#ifndef PROCESS_ARRAY_H
#define PROCESS_ARRAY_H
#include "process.h"

typedef struct Process_Array {
    Process array[100];
    int num;
} Process_Array;

int proc_waiting(int t, Process_Array p_A);
int proc_remaining(Process_Array p_A);
int next_proc(Process_Array p_A);
void print_array(Process_Array p_A);
int next_proc_shortest(Process_Array p_A);

#endif