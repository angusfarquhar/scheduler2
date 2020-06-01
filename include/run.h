#include "process.h"
#include "args.h"
#include "process_array.h"

int run(Args a);

int run(Args a);
void read(char *filename);
void ff(Process_Array p_A);
void ff_p(Process_Array p_A, int memory);
void rr(Process_Array p_A, int quantum);
void rr_p(Process_Array p_A, int memory, int quantum);
void rr_vm(Process_Array p_A, int memory, int quantum);
void print_running(Process p);