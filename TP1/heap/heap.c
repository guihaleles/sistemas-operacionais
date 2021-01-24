 
//Fila de prioridade utilizando heap, adaptado de  sedgwick
#ifndef HEAP_C
#define HEAP_C
#include "heap.h"

int size = 0;

typedef struct Nodes_heap_t {
    int i; // priority id
    void * object_data_ptr;
}Node_heap_t;

void swap(Node_heap_t **a, Node_heap_t **b) {
  Node_heap_t* temp = *b;
  *b = *a;
  *a = temp;
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
    if (l < size && heap[l]->i > heap[largest]->i)
      largest = l;
    if (r < size && heap[r]->i > heap[largest]->i)
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&heap[i], &heap[largest]);
      heapify(heap, size, largest);
    }
  }
}

// Function to insert an element into the tree
void insert(Node_heap_t* heap[], Node_heap_t* newNum) {
  if (size == 0) {
    heap[0] = newNum;
    size += 1;
  } else {
    heap[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(heap, size, i);
    }
  }
}

// Function to delete an element from the tree
void deleteRoot(Node_heap_t* heap[], Node_heap_t* num) {
  int i;
  for (i = 0; i < size; i++) {
    if (num->i == heap[i]->i)
      break;
  }

  swap(&heap[i], &heap[size - 1]);
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(heap, size, i);
  }
}

// Print the heap
void printheap(Node_heap_t* heap[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", heap[i]->i);
  printf("\n");
}

// Driver code
int main() {
  Node_heap_t* heap[10];
  Node_heap_t* objects = (Node_heap_t*) calloc(10,sizeof(objects));
  for (int i=0; i<10; i++){
    objects[i].i=i;
  }
  insert(heap, &objects[3]);
  insert(heap, &objects[4]);
  insert(heap, &objects[9]);
  insert(heap, &objects[5]);
  insert(heap, &objects[2]);

  printf("Max-Heap heap: ");
  printheap(heap, size);

  deleteRoot(heap, &objects[5]);

  printf("After deleting an element: ");

  printheap(heap, size);
  
    deleteRoot(heap, &objects[9]);

  printf("After deleting an element: ");

  printheap(heap, size);
  
  
  return 0;
}

#endif
