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
} Process;

#endif