 
//Fila de prioridade utilizando queue, adaptado de  sedgwick
#ifndef queue_C
#define queue_C
#include "queue.h"
#include <stdbool.h>
int h_size = 0;
extern int h_size;
typedef struct Node_t {
    Node_t* next, *previous;
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

// Function to queueify the tree
void queueify(Node_t* queue[], int h_size, int i) {
  if (h_size == 1) {
    printf("Single element in the queue");
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < h_size && queue[0]->comparison(queue[l], queue[largest]))
      largest = l;
    if (r < h_size &&  queue[0]->comparison(queue[r],queue[largest]))
      largest = r;

    // Swap and continue queueifying if root is not largest
    if (largest != i) {
      swap(&queue[i], &queue[largest]);
      queueify(queue, h_size, largest);
    }
  }
}

// Function to insert an element into the tree
void insert(Node_t* queue, Node_t* item) {
  queue->next = item;
  item->next = queue;
}

// Function to delete an element from the tree
Node_t* pop(Node_t** queue, Node_t* item) {
  Node_t* first, end;
  first =  (*queue);
  while(end->next != first)
    end = end->next;
  
  end->next = first->next;
  *queue = first->next;
  return first;
}

// Print the queue
void print_queue(Node_t** queue, int h_size) {
  for (Node_t* iter = *queue; iter->next != iter; iter = iter->next)
    printf("%d ", iter->i);
  printf("\n");
}

// Driver code
int main() {
  Node_t* queue;
  Node_t* items = (Node_t*) calloc(10,sizeof(items));
  for (int i=0; i<10; i++){
    items[i].i=i;
  }
  insert(queue, &items[3]);
  insert(queue, &items[4]);
  insert(queue, &items[9]);
  insert(queue, &items[5]);
  insert(queue, &items[2]);

  printf("Max-queue queue: ");
  print_queue(queue, h_size);

  pop(queue, &items[5]);

  printf("After deleting an element: ");

  print_queue(queue, h_size);
  
  pop(queue, &items[9]);

  printf("After deleting an element: ");

  print_queue(queue, h_size);
  
  
  return 0;
}

#endif