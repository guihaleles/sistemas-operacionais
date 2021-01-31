 
//Fila de prioridade utilizando queue, adaptado de  sedgwick
#ifndef queue_C
#define queue_C
#include "queue.h"
#include <stdbool.h>
int h_size = 0;
extern int h_size;
typedef struct Node_t {
    int i;
    struct Node_t* next, *previous;
    void * data;
    bool (*comparison)(struct Node_t *a, struct Node_t *b);
} Node_t;



bool comparison(Node_t *a, Node_t *b) {
return  a->i > b->i;
}
void init_queue(Node_t** queue){*queue = NULL;}

//void update_queue(Node_t** queue){}

// Function to insert an element into the tree
void insert(Node_t** queue, Node_t* item) {
  Node_t** iter = queue;
  if(*queue == NULL)
    *queue = item;
  while ((*iter)->next != NULL && (*iter) != *queue && (*iter)->comparison(item, (*iter)->next)){
    (*iter) = (*iter)->next;
  }
  item->next = (*iter)->next;
  (*iter)->next = item;
  *queue = item;
  
}

// Function to delete an element from the tree
Node_t* pop(Node_t** queue) {
  Node_t* first, *end, *pop;
  first =  (*queue);
  end = (*queue);
  while(end->next->next != NULL && end->next->next != first)
    end = end->next;
  pop = end->next;
  end->next = first;
  return pop;
}

// Print the queue
void print_queue(Node_t** queue) {
  for (Node_t* iter = *queue;
     iter->next != NULL && iter != *queue; iter = iter->next)
    printf(" %d ", iter->i);
  printf("\n");
}


// Driver code
int main() {
  Node_t* queue;
  queue = NULL;
  Node_t* items = (Node_t*) calloc(10,sizeof(items));
  for (int i=0; i<10; i++){
    items[i].i=i;
    //items[i].comparison = comparison;
  }
  printf("Max-queue queue: "); 
  insert(queue, &items[3]);
  insert(queue, &items[4]);
  insert(queue, &items[9]);
  insert(queue, &items[5]);
  insert(queue, &items[2]);

  print_queue(queue);

  pop(queue);

  printf("After deleting an element: ");

  print_queue(queue);
  
  pop(queue);

  printf("After deleting an element: ");

  print_queue(queue);
  
  
  return 0;
}

#endif