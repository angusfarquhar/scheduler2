#ifndef MEMORY_H
#define MEMORY_H
#include "process.h"

#define HOLE NULL

typedef struct node { 
    Process p;
    int type;
    int start;
    int size;   
    struct node *next;
} Node;

void printList();
void insertFirst(Process p, int start, int size);
Node* deleteFirst();
bool isEmpty();
int length();
Node* find(Process p);
Node* delete(Process p);

#endif