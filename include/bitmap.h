#ifndef MEMORY_H
#define MEMORY_H
#include "process.h"

typedef struct Bitmap { 
    int array[100];
    int start_time[100];
    int load_time[100];
    int num;
} Bitmap;

int room_for_process(Process p);
void init_bitmap();
void print_bitmap();
void remove_process(Process p);
void print_mem_usage(Process p);
void print_mem_addresses(Process p);
int room_for_vm(Process p);
void remove_oldest_pages(int num, int next);
int oldest_page(int next); 
int cmpfunc (const void * a, const void * b);

#endif