/* Roll No: EE23B022
Name: Deepak Charan S
Date 07/09/2023 
Version: 1.3
Description: Read from a data file (argv[1]) of integers into a linked list and print out the integers using quick sort of the list.
Input: the name of the input file (from which we have to store its integers in a linked list and do quick sort on them) 
Output:The sorted linked list of the data file.
*/

#include <stdio.h>
#include <stdlib.h>


struct node {     //Defining a doubly linked list node
    int data;
    struct node* next;
};


struct node* createnode(int data) {  // Function to create a new node
    struct node* new = (struct node*)malloc(sizeof(struct node));  //memory allocation of the data in nodes of the linked list
    new->data = data;      
    new->prev = NULL;
    new->next = NULL;
    return new;
}


void insertnode(struct node** head, int data) { // Function to insert a new node at the end of the doubly linked list
    struct node* new = createnode(data);
    if (*head == NULL) {
        *head = new;
    }
     else {
        struct node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
        new->prev = current;
    }
}

void print(struct node* head) { // Function to print the doubly linked list
    struct node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}
 
void swap(int* a, int* b) {        // Function to swap two pointed integers from in the list
    int temp = *a;
    *a = *b;
    *b = temp;
}


struct node* partition(struct node* low, struct node* high) { // Partition function for Quick Sort
    int pivot = high->data;
    struct node* i = low->prev;

    for (struct node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == NULL) ? low : i->next;
            swap(&(i->data), &(j->data));   //Swap the low and high element according to the pivot
        }
    }

    i = (i == NULL) ? low : i->next;
    swap(&(i->data), &(high->data));
    return i;
}

void quickSort(struct node* low, struct node* high) {       //function to implement quick sort algorithm
    if (high != NULL && low != high && low != high->next) {
        struct node* pivot = partition(low, high);     
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}

int main(int argc, char* argv[]) {
    FILE* fp = fopen(argv[1], "r");
    struct node* head = NULL;
    int value;
    while (fscanf(fp, "%d", &value) == 1) { // Read integers from the file and insert them into the doubly linked list
        insertnode(&head, value);
    }

    fclose(fp);
    struct node* tail = head; 
    while (tail->next != NULL) {
        tail = tail->next;
    }
    quickSort(head, tail);   //sorting the integers from the file using quick sort
    print(head);
    
    return 0;
}
