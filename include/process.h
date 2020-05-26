#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
    int t;
    int id;
    int kb;
    int runtime;
    int remaining;
} Process;

#endif