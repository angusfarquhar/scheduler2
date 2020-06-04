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
    //fprintf(stderr, "room_bitmap[0] = %d\n", bitmap.array[0]);
    // fprintf(stderr, "count = %d\n", count);
    //fprintf(stderr, "p.pages = %d\n", p.pages);
    for (int i=0; i<bitmap.num; i++) {  
        if (count == 0) {
            return 1;
        }      
        if (bitmap.array[i] == -1 || bitmap.array[i]  == p.id) {
            count--;
            //add process to bitmap
            bitmap.array[i] = p.id;
            bitmap.start_time[i] = global_t;

        }
   }
    //fprintf(stderr, "countend = %d\n", count);
    return 0;

}

//returns -1 if process can't run 0 if it fits or positive int for the amount of pages missing
int room_for_vm(Process p) 
{
    int is_room = 0;
    
    int count = p.pages;
    int single_load = p.load_time / p.pages;
    int load_count = 0; 
    int min_to_run = count - 4;
    fprintf(stderr, "p.pages = %d\n", p.pages);
    //check if process already in there
    for (int i=0; i<bitmap.num; i++) {
        if (p.id == bitmap.array[i]) {
            count--;
        }
    }
    // fprintf(stderr, "room_bitmap[0] = %d\n", bitmap.array[0]);
    // fprintf(stderr, "count = %d\n", count);
    // fprintf(stderr, "p.pages = %d\n", p.pages);
    for (int i=0; i<bitmap.num; i++) {  
        if (count == 0) {
            is_room =1;
        }      
        if (bitmap.array[i] == -1) {
            count--;
            //add process to bitmap
            bitmap.array[i] = p.id;
            bitmap.start_time[i] = global_t;
            bitmap.load_time[i] = p.load_time / p.pages;
            load_count += single_load;

        }
   }
   
    fprintf(stderr, "countend = %d\n", count);
    fprintf(stderr, "remaining before count = %d\n", p.remaining);
    if (count <= min_to_run) {
        
        is_room = 1;
        //adding the penalty
        
    }
    p.remaining += count;
    printf("%d, RUNNING, id=%d, remaining-time=%d", global_t, p.id, p.remaining);
    printf(", load-time=%d", load_count);
    print_mem_usage(p);
    print_mem_addresses(p);
    p.mem_start = global_t;
    global_t += load_count;

    if (is_room) {
        return count;
    } else {
        return -1;
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

//removes the oldest processes in the bitmap
void remove_oldest_pages(int num, int next) {
    //print_bitmap();
    int removed[100] = {-1};
    printf("%d, EVICTED", global_t);
    printf(", mem-addresses=["); //TODO change back to printf
    int count = 0;

    for (int i=0; i<bitmap.num; i++) {
        if (bitmap.array[i] == next) {
            num--; 
        }
    }

    for (int i=0; i<num; i++) {
        int remove = oldest_page(next); 
        fprintf(stderr, "oldest page %d\n", remove); 
        if (remove != -1) {
            bitmap.array[remove] = -1;
            bitmap.start_time[remove] = -1;
            removed[i] = remove;
        }
        
        
          
        
        //time moves forward by the load time per page
        //global_t += single_load;

        
   }
   qsort(removed, num-count, sizeof(int), cmpfunc);
   for (int i = 0; i<num; i++) {
       if (i >0) {
            printf(",%d", removed[i]);
        }

        
        if (i == 0) {
            printf("%d", removed[i]);
        }
   }
        
   printf("]\n");
   return;
}

//returns index in bitmap of oldest page so we can remove it first
int oldest_page(int next) {
    int min = 1000000;
    fprintf(stderr, "min at start= %d", min);
    fprintf(stderr, "next at start= %d", next);
    int index = 0;
    print_bitmap();
    for (int i=0; i<bitmap.num; i++) {                                      //don't want to remove a page if it is proc up next 
        if (bitmap.start_time[i] < min && bitmap.start_time[i] != -1 && bitmap.array[i] != next) {
            fprintf(stderr, "start_time[%d] %d\n", i, bitmap.start_time[i]);
            min = bitmap.start_time[i];
            index = i;
        }
    }
    return index;
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

void init_bitmap() {
    for (int i=0; i<bitmap.num; i++) {
        bitmap.array[i] = -1;
        bitmap.start_time[i] = -1;
        bitmap.load_time[i] = -1;
        //fprintf(stderr, "init_bitmap[%d] = %d\n",i, bitmap.array[i]);

    }
    return;
}

void print_bitmap() {
    fprintf(stderr, "\n");
    for (int i=0; i<bitmap.num; i++) {
        fprintf(stderr, "print_bitmap[%d] = [%d],[%d]\n",i, bitmap.array[i], bitmap.start_time[i]);

    }
    fprintf(stderr, "\n");
    return;
}

//adapted from https://www.tutorialspoint.com/learn_c_by_examples/program_to_calculate_percentage_in_c.htm
void print_mem_usage(Process p) {

    int count = 0;
    for (int i=0; i<bitmap.num; i++) {
        if (bitmap.array[i] > 0) {
            count++;
        }
    }

   float percentage = (float)count / bitmap.num * 100.0;
   percentage = percentage + 0.9; 
   printf(", mem-usage=%d%%", (int)percentage);
}

//taken from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
