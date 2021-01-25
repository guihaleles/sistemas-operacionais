#ifndef person_C
#define person_C
//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#define num_persons 8

#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
typedef struct Person_t
{
    char *name;
    struct Person_t *partner;
    int priority,
        id,
        idx_partner;
    Node_heap_t *priority_node;
    int *precedences;
} Person_t;

// Priorities Matrix:
const char persons_names[num_persons][20] = {"Sheldon", "Howard", "Leonard", "Stuart",
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
const int priorities[num_persons][num_persons] = {
    {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    8
    {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     8
    {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    8
    {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
    {0, 0, 0, 0, 1, 0, 0, 1}, //Amy        1
    {0, 0, 0, 0, 0, 1, 0, 1}, //Bernadette 1
    {0, 0, 0, 0, 0, 0, 1, 1}, //Penny      1
    {0, 0, 0, 0, 0, 0, 0, 1}  //Kripke     0
};

bool person_comparison(Node_heap_t *a, Node_heap_t *b)
{
    Person_t *person_a, *person_b;
    person_a = (Person_t *)a->data;
    person_b = (Person_t *)b->data;

    if (person_a->priority > person_b->priority)
        return true;
    if (
        (person_a->priority == person_b->priority) &&
        (person_a->precedences[person_b->id] > person_b->precedences[person_a->id]))
        return true;

    return false;
}
void init_persons(Person_t persons[])
{
    for (int i = 0; i < num_persons; i++)
    {
        persons[i].id = i;
        persons[i].name = persons_names[i];
        persons[i].idx_partner = partners[i];
        persons[i].partner = &persons[partners[i]];
        persons[i].priority_node = (Node_heap_t *)malloc(sizeof(Node_heap_t));
        int priority = 0;
        for (int j = 0; j < num_persons; j++)
            priority += priorities[i][j];
        persons[i].priority_node->data = (Person_t*)(&persons[i]);
        persons[i].priority_node->comparison = person_comparison;
        persons[i].priority_node->i = priority;
        persons[i].precedences = priorities[i];
    }
}
void enqueue_person(Node_heap_t* heap[], Person_t* person) {  
    heap_insert(&heap, person->priority_node);
}

void dequeue_person(Node_heap_t* heap[], Person_t* person) {
    deleteRoot(&heap, person->priority_node);
    return person;
}

void queue_first(Node_heap_t* heap[], Person_t* person) {
    return heap[0]->data;
}
// Print the heap
void print_queue(Node_heap_t* heap[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", ((Person_t*)(heap[i]->data))->name);
  printf("\n");
}

int main(int argc, char *argv[])
{

    Node_heap_t *heap[10];

    Person_t *persons = (Person_t*) calloc(num_persons,sizeof(Person_t));
    init_persons(persons);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[3]);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[4]);
    print_queue(heap, num_persons);
    dequeue_person(heap, &persons[5]);
    print_queue(heap, num_persons);
    dequeue_person(heap, &persons[2]);
    print_queue(heap, num_persons);
    printf("Max-Heap heap: ");
    print_queue(heap, size);

    return 0;
}

#endif