 
//Fila de prioridade utilizando heap, adaptado de  sedgwick
#ifndef HEAP_C
#define HEAP_C
#include "heap.h"
#include <stdbool.h>
int h_size = 0;
extern int h_size;
typedef struct Node_t {
    int i; // priority id
    void * data;
    bool (*comparison)(struct Node_t *a, struct Node_t *b);
} Node_t;

void swap(Node_t **a, Node_t **b) {
  Node_t* temp = *b;
  *b = *a;
  *a = temp;
}

bool comparison(Node_t *a, Node_t *b) {
return  a->i > b->i;
}

// Function to heapify the tree
void heapify(Node_t* heap[], int h_size, int i) {
  if (h_size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < h_size && heap[0]->comparison(heap[l], heap[largest]))
      largest = l;
    if (r < h_size &&  heap[0]->comparison(heap[r],heap[largest]))
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&heap[i], &heap[largest]);
      heapify(heap, h_size, largest);
    }
  }
}

// Function to heap_insert an element into the tree
void heap_insert(Node_t* heap[], Node_t* item) {
  if (h_size == 0) {
    heap[0] = item;
    h_size += 1;
  } else {
    heap[h_size] = item;
    h_size += 1;
    for (int i = h_size / 2 - 1; i >= 0; i--) {
      heapify(heap, h_size, i);
    }
  }
}

// Function to delete an element from the tree
Node_t* deleteRoot(Node_t* heap[], Node_t* item) {
  int i;
  for (i = 0; i < h_size; i++) {
    if (item->i == heap[i]->i)
      break;
  }
  
  swap(&heap[i], &heap[h_size - 1]);
  Node_t* ret = heap[h_size - 1];
  heap[h_size - 1] = NULL;
  h_size -= 1;
  for (int i = h_size / 2 - 1; i >= 0; i--) {
    heapify(heap, h_size, i);
  }
  return ret;
}

// Print the heap
void printheap(Node_t* heap[], int h_size) {
  for (int i = 0; i < h_size; ++i)
    printf("%d ", heap[i]->i);
  printf("\n");
}

// Driver code
int test() {
  Node_t* heap[10];
  Node_t* items = (Node_t*) calloc(10,sizeof(items));
  for (int i=0; i<10; i++){
    items[i].i=i;
  }
  heap_insert(heap, &items[3]);
  heap_insert(heap, &items[4]);
  heap_insert(heap, &items[9]);
  heap_insert(heap, &items[5]);
  heap_insert(heap, &items[2]);

  printf("Max-Heap heap: ");
  printheap(heap, h_size);

  deleteRoot(heap, &items[5]);

  printf("After deleting an element: ");

  printheap(heap, h_size);
  
  deleteRoot(heap, &items[9]);

  printf("After deleting an element: ");

  printheap(heap, h_size);
  
  
  return 0;
}

#endif