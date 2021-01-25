 
//Fila de prioridade utilizando heap, adaptado de  sedgwick
#ifndef HEAP_C
#define HEAP_C
#include "heap.h"
#include <stdbool.h>
int size = 0;

typedef struct Node_heap_t {
    int i; // priority id
    void * data;
    bool (*comparison)(struct Node_heap_t *a, struct Node_heap_t *b);
} Node_heap_t;

void swap(Node_heap_t **a, Node_heap_t **b) {
  Node_heap_t* temp = *b;
  *b = *a;
  *a = temp;
}

bool comparison(Node_heap_t *a, Node_heap_t *b) {
return  a->i > b->i;
}

// Function to heapify the tree
void heapify(Node_heap_t* heap[], int size, int i) {
  if (size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && heap[i]->comparison(heap[l], heap[largest]))
      largest = l;
    if (r < size &&  heap[i]->comparison(heap[r],heap[largest]))
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&heap[i], &heap[largest]);
      heapify(heap, size, largest);
    }
  }
}

// Function to heap_insert an element into the tree
void heap_insert(Node_heap_t* heap[], Node_heap_t* item) {
  if (size == 0) {
    heap[0] = item;
    size += 1;
  } else {
    heap[size] = item;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(heap, size, i);
    }
  }
}

// Function to delete an element from the tree
Node_heap_t* deleteRoot(Node_heap_t* heap[], Node_heap_t* item) {
  int i;
  for (i = 0; i < size; i++) {
    if (item->i == heap[i]->i)
      break;
  }

  swap(&heap[i], &heap[size - 1]);
  heap[size - 1] = NULL;
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(heap, size, i);
  }
  return item;
}

// Print the heap
void printheap(Node_heap_t* heap[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", heap[i]->i);
  printf("\n");
}

// Driver code
int test() {
  Node_heap_t* heap[10];
  Node_heap_t* items = (Node_heap_t*) calloc(10,sizeof(items));
  for (int i=0; i<10; i++){
    items[i].i=i;
  }
  heap_insert(heap, &items[3]);
  heap_insert(heap, &items[4]);
  heap_insert(heap, &items[9]);
  heap_insert(heap, &items[5]);
  heap_insert(heap, &items[2]);

  printf("Max-Heap heap: ");
  printheap(heap, size);

  deleteRoot(heap, &items[5]);

  printf("After deleting an element: ");

  printheap(heap, size);
  
  deleteRoot(heap, &items[9]);

  printf("After deleting an element: ");

  printheap(heap, size);
  
  
  return 0;
}

#endif