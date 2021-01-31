
// insertion and 
// deletion in Circular Queue 
#include <stdlib.h>
#include <stdio.h>  
// Structure of a Node 
typedef struct Node { 
    void *data; 
    struct Node* link; 
}Node; 
  
typedef struct Queue { 
    struct Node *front, *rear; 
}Queue; 
  
// Function to create Circular queue 
void enQueue(Queue* q, void *value) 
{ 
    struct Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = value; 
    if (q->front == NULL) 
        q->front = temp; 
    else
        q->rear->link = temp; 
  
    q->rear = temp; 
    q->rear->link = q->front; 
} 
  
// Function to delete element from Circular Queue 
int deQueue(Queue* q) 
{ 
    if (q->front == NULL) { 
        printf("Queue is empty"); 
        return -1; 
    } 
  
    // If this is the last node to be deleted 
    void *value; // Value to be dequeued 
    if (q->front == q->rear) { 
        value = q->front->data; 
        free(q->front); 
        q->front = NULL; 
        q->rear = NULL; 
    } 
    else // There are more than one nodes 
    { 
        struct Node* temp = q->front; 
        value = temp->data; 
        q->front = q->front->link; 
        q->rear->link = q->front; 
        free(temp); 
    } 
  
    return value; 
} 
  
// Function displaying the elements of Circular Queue 
void displayQueue(struct Queue* q) 
{ 
    struct Node* temp = q->front; 
    printf("\nElements in Circular Queue are: "); 
    while (temp->link != q->front) { 
        printf("%d ", temp->data); 
        temp = temp->link; 
    } 
    printf("%d", temp->data); 
} 
  
/* Driver of the program */
int main() 
{ 
    // Create a queue and initialize front and rear 
    Queue* q = (Queue*) malloc(sizeof(Queue));; 
    q->front = q->rear = NULL; 
    int v1=15, v2=22, v3=6, v4=9, v5=6;
    // Inserting elements in Circular Queue 
    enQueue(q, &v1); 
    enQueue(q, &v2); 
    enQueue(q, &v3); 
  
    // Display elements present in Circular Queue 
    displayQueue(q); 
  
    // Deleting elements from Circular Queue 
    printf("\nDeleted value = %d", deQueue(q)); 
    printf("\nDeleted value = %d", deQueue(q)); 
  
    // Remaining elements in Circular Queue 
    displayQueue(q); 
  
    enQueue(q, &v4); 
    enQueue(q, &v5); 
    displayQueue(q); 
  
    return 0; 
} 
