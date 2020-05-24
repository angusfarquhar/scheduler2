#ifndef PROCESS_ARRAY_H
#define PROCESS_ARRAY_H
#include "process.h"

typedef struct Process_Array {
    Process array[100];
    int num;
} Process_Array;

int proc_remaining(int t, Process_Array p_A);

#endif