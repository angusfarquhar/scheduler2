//modified from https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/process.h"
#include "../include/bitmap.h"

extern Bitmap bitmap;
extern int global_t;

//returns 0 if process can't fit 1 if it can and adds the process id to bitmap at corresponding page
int room_for_process(Process p) 
{
    int count = p.pages;
    fprintf(stderr, "room_bitmap[0] = %d\n", bitmap.array[0]);
    // fprintf(stderr, "count = %d\n", count);
    fprintf(stderr, "p.pages = %d\n", p.pages);
    for (int i=0; i<bitmap.num; i++) {  
        if (count == 0) {
            return 1;
        }      
        if (bitmap.array[i] == -1 || bitmap.array[i]  == p.id) {
            count--;
            //add process to bitmap
            bitmap.array[i] = p.id;

        }
   }
    fprintf(stderr, "countend = %d\n", count);
    return 0;

}

int room_for_vm(Process p) 
{
    int count = p.pages;
    // fprintf(stderr, "room_bitmap[0] = %d\n", bitmap.array[0]);
    // fprintf(stderr, "count = %d\n", count);
    // fprintf(stderr, "p.pages = %d\n", p.pages);
    for (int i=0; i<bitmap.num; i++) {  
        if (count == 0) {
            return 1;
        }      
        if (bitmap.array[i] == -1) {
            count--;
            //add process to bitmap
            bitmap.array[i] = p.id;

        }
   }
   //if it's been allocated more than 4 pages into memory it's fine!
   if (p.pages-count >= 4) {
       return 1;
   }
   
    fprintf(stderr, "countend = %d\n", count);
    return 0;

}


void remove_process(Process p) {
    for (int i=0; i<bitmap.num; i++) {       
        if (bitmap.array[i] == p.id) {
            bitmap.array[i] = -1;

        }
   }
   p.running = 0;
   return;
}

void remove_process_vm(Process p) {
    for (int i=0; i<4; i++) {       
        if (bitmap.array[i] == p.id) {
            bitmap.array[i] = -1;

        }
   }
   p.running = 0;
   return;
}

void init_bitmap() {
    for (int i=0; i<bitmap.num; i++) {
        bitmap.array[i] = -1;
        //fprintf(stderr, "init_bitmap[%d] = %d\n",i, bitmap.array[i]);

    }
    return;
}

void print_bitmap() {
    for (int i=0; i<bitmap.num; i++) {
        //fprintf(stderr, "print_bitmap[%d] = %d\n",i, bitmap.array[i]);

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
   percentage = percentage + 0.9; 
   printf(", mem-usage=%d%%", (int)percentage);
}

void print_mem_addresses(Process p) {
    printf(", mem-addresses=[");
    int count = 0;
    for (int i=0; i<bitmap.num; i++) {
        
        if (p.id == bitmap.array[i]) {
            count++;
            if (count >1) {
                printf(",%d", i);
            }
                
        }
        if (count == 1) {
            printf("%d", i);
        }
        // if (i != bitmap.num-1) {
        //     printf(",");
        // }
        
    }
    printf("]\n");

}