#ifndef person_C
#define person_C
//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "heap/heap.h"

#define num_persons 8
#define get_person(x) ((Person_t*)x->data)
#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
typedef struct Person_t
{
    char name[20];
    struct Person_t *partner;
    int priority,
        id,
        idx_partner;
    Node_heap_t *priority_node;
    int *precedences;
    int numberOfUses;
    bool inTheQueue;
} Person_t;

// Priorities Matrix:
char persons_names[num_persons][20] = {"Sheldon", "Howard", "Leonard", "Stuart",
                                             "Penny", "Bernardette", "Amy", "Kripke"};

int partners[num_persons] = {
    4,  //Sheldon & Amy
    5,  //Howard & Bernadette
    7,  //Leonard & Penny
    -1, //Stuart
    0,  //Amy & Sheldon
    1,  //Bernadette & Howard
    2,  //Penny & Leonard
    -1  //Kripke
};
int priorities[num_persons][num_persons] = {
    {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    7
    {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     7
    {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    7
    {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
    {0, 0, 0, 0, 1, 0, 0, 1}, //Amy        2
    {0, 0, 0, 0, 0, 1, 0, 1}, //Bernadette 2
    {0, 0, 0, 0, 0, 0, 1, 1}, //Penny      2
    {0, 0, 0, 0, 0, 0, 0, 1}  //Kripke     1
};

bool person_comparison(Node_heap_t *a, Node_heap_t *b)
{
    Person_t *person_a, *person_b;
    person_a = (Person_t *)a->data;
    person_b = (Person_t *)b->data;

    if (person_a->priority > person_b->priority)
        return true;
    else{
        
        if (
            (person_a->priority == person_b->priority) &&
            (person_a->precedences[person_b->id] > person_b->precedences[person_a->id])
        )
            return true;
    }

    return false;
}
void init_persons(Person_t persons[], int numberOfUses)
{
    for (int i = 0; i < num_persons; i++)
    {
        persons[i].id = i;
        persons[i].numberOfUses = numberOfUses;
        persons[i].inTheQueue = false;
        strcpy(persons[i].name, persons_names[i]);
        persons[i].idx_partner = partners[i];
        persons[i].partner = &persons[partners[i]];
        persons[i].priority_node = (Node_heap_t *)malloc(sizeof(Node_heap_t));
        persons[i].precedences = priorities[i];
        int priority = 0;
        for (int j = 0; j < num_persons; j++)
            priority += persons[i].precedences[j];
        persons[i].priority = priority;            
        persons[i].priority_node->data = (Person_t*)(&persons[i]);
        persons[i].priority_node->comparison = person_comparison;
        persons[i].priority_node->i = priority;
        
    }
}
void enqueue_person(Node_heap_t* heap[], Person_t* person) {  
    heap_insert(heap, person->priority_node);
}

Person_t*  dequeue_person(Node_heap_t* heap[]) {
    return ( Person_t*)deleteRoot(heap, heap[0])->data;
}

Person_t* queue_first(Node_heap_t* heap[]) {
    return ((Person_t*)(heap[0]->data));
}
// Print the heap
void print_queue(Node_heap_t* heap[], int h_size) {
  for (int i = 0; i < h_size; ++i)
    if (heap[i] != NULL)
        printf("%s: %d ", ((Person_t*)(heap[i]->data))->name, 
        ((Person_t*)(heap[i]->data))->priority);
  printf("\n");
}

void print_persons(Person_t persons[]) {
  for (int i = 0; i < h_size; i++)
        printf("%s: %d ", persons[i].name, persons[i].priority);
  printf("\n");
}
bool check_deadlock(Node_heap_t* heap[]){
    //Return true if there is a deadlock
    int ids_before[h_size];
    for(int i=0; i<h_size;i++)
        ids_before[i] = get_person(heap[i])->id;
    for (int i = h_size / 2 - 1; i >= 0; i--)
        heapify(heap, h_size, i);
    for(int i=0; i<h_size;i++)
        if (ids_before[i] != get_person(heap[i])->id)
            return true;
    return false;    
}
// int test(int argc, char *argv[])
// {
//     //int h_size = 0;
//     Node_heap_t *heap[10];
//     for (int i=0; i<num_persons; i++)
//         heap[i]=NULL;
    
//     Person_t *persons = (Person_t*) calloc(num_persons,sizeof(Person_t));
//     init_persons(persons, 5);
//     print_persons(persons);
//     print_queue(heap, num_persons);
//     enqueue_person(heap, &persons[4]);
//     print_queue(heap, num_persons);
//     enqueue_person(heap, &persons[3]);
//     print_queue(heap, num_persons);
//     enqueue_person(heap, &persons[2]);
//     print_queue(heap, num_persons);
//     enqueue_person(heap, &persons[1]);
//     print_queue(heap, num_persons);
//      enqueue_person(heap, &persons[5]);
//     print_queue(heap, num_persons);
//     if (check_deadlock(heap))
//         printf("Deadlock!!!\n");
//     enqueue_person(heap, &persons[0]);
//     print_queue(heap, num_persons);
//     Person_t *p = queue_first(heap); 
//     printf("Max-Heap heap: %s \n", p->name );
//     if (check_deadlock(heap))
//         printf("Deadlock!!!\n");
//     p = dequeue_person(heap);
//     printf("Dequeue: %s \n", p->name );
//     if (check_deadlock(heap))
//         printf("Deadlock!!!\n");
//     print_queue(heap, num_persons);
//     p = dequeue_person(heap);
//     printf("Dequeue: %s \n", p->name );
//     print_queue(heap, num_persons);
//     printf("\nDone \n");
//     return 0;
// }

#endif