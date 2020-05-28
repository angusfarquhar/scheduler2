//modified from https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/process.h"
#include "../include/memory.h"

Node *head = NULL;
Node *current = NULL;

/////////////////////////////////////////////////////////////

void insert_proc(Process p) {
    //start from the first link
   Node* current = head;

   //if list is empty
   if(head == NULL) {
      insertFirst(p, 0, p.kb);
   }

   //navigate through list
   while(current->type != HOLE) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

//display the list
void printList() {
   Node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->type,ptr->start);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert new node at the first location
void insertFirst(Process p, int start, int size) {
   //create a new node
   Node *new = (Node*) malloc(sizeof(Node));
	
   new->p = p;
   new->start = start;
   new->size = size;

	
   //point it to old first node
   new->next = head;
	
   //point first to new first node
   head = new;
}

//delete first item
Node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   Node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
Node* find(Process p) {

   //start from the first link
   Node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->p.id != p.id) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

//delete a link with given key
Node* delete(Process p) {

   //start from the first link
   Node* current = head;
   Node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->p.id != p.id) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}

