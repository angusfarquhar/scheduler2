//modified from https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/process.h"
#include "../include/bitmap.h"

extern Bitmap bitmap;
extern int global_t;

//returns 0 if process can't fit, adds the process id to bitmap at corresponding page
int room_for_process(Process p) 
{
    int count = p.pages;
    fprintf(stderr, "room_bitmap[0] = %d\n", bitmap.array[0]);
    fprintf(stderr, "count = %d\n", count);
    fprintf(stderr, "p.pages = %d\n", p.pages);
    for (int i=0; i<bitmap.num; i++) {       
        if (bitmap.array[i] == -1) {
            count--;
            bitmap.array[i] = p.id;

        }
   }
   fprintf(stderr, "countend = %d\n", count);
   if (count == 0) {
       return 1;
   } else {
       return 0;
   }
}

void remove_process(Process p) {
    for (int i=0; i<bitmap.num; i++) {       
        if (bitmap.array[i] == p.id) {
            bitmap.array[i] = -1;

        }
   }
   return;
}

void init_bitmap() {
    for (int i=0; i<bitmap.num; i++) {
        bitmap.array[i] = -1;
        fprintf(stderr, "init_bitmap[%d] = %d\n",i, bitmap.array[i]);

    }
    return;
}

void print_bitmap() {
    for (int i=0; i<bitmap.num; i++) {
        fprintf(stderr, "print_bitmap[%d] = %d\n",i, bitmap.array[i]);

    }
    return;
}

//adapted from https://www.tutorialspoint.com/learn_c_by_examples/program_to_calculate_percentage_in_c.htm
void print_mem_usage(Process p) {

    int count = 0;
    for (int i=0; i<bitmap.num; i++) {
        if (p.id == bitmap.array[i]) {
            count++;
        }
    }

   float percentage = (float)count / bitmap.num * 100.0;

   printf(", mem-usage=%.0f%%", percentage);
}

void print_mem_addresses(Process p) {
    printf(", mem-addresses=[");
    for (int i=0; i<bitmap.num; i++) {
        if (p.id == bitmap.array[i]) {
            printf("%d", i);
        }
        if (i != bitmap.num-1) {
            printf(",");
        }
        
    }
    printf("]\n");

}