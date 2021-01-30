#ifndef HEAP_INT
#define HEAP_INT




#include <stdio.h>

void swap(int *a, int *b);

// Function to heapify the tree
void heapify(int array[], int size, int i) ;

// Function to insert an element into the tree
void insert(int array[], int newNum) ;

// Function to delete an element from the tree
void deleteRoot(int array[], int num);

// Print the array
void printArray(int array[], int size) ;

#endif