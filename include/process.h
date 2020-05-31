#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
    int t;
    int id;
    int kb;
    int mem_start;
    int runtime;
    int remaining;
    int time_queued;
    int has_run;
    int end_time;
    int load_time;
    float turnaround;
    float time_overhead;
} Process;

#endif