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
typedef enum {WANT_COOK, COOKING, EATING, WORKING } State_t;

#define num_persons 8
#define get_person(x) ((Person_t*)x->data) // get person from node
#define DETERMINISTIC true

typedef struct Person_t
{
    char name[20];
    struct Person_t *partner;
    int priority,
        id,
        idx_partner;
    Node_t *priority_node;
    int *precedences;
    int numberOfUses;
    bool released;
    State_t state;
    bool inTheQueue;
    pthread_mutex_t mutex;
    bool has_Partner = false;
    bool is_girlfriend = false;
} Person_t;
// Priorities Matrix:
char persons_names[num_persons][20] = {"Sheldon", "Howard", "Leonard", "Stuart",
                                             "Penny", "Bernardette", "Amy", "Kripke"};
int is_girlfriend[num_persons] = {false, false, false, false, true, true, true, false};

int partners[num_persons] = {
    4,  //Sheldon & Amy
    5,  //Howard & Bernadette
    6,  //Leonard & Penny
    -1, //Stuart
    0,  //Amy & Sheldon
    1,  //Bernadette & Howard
    2,  //Penny & Leonard
    -1  //Kripke
};
int prec[num_persons][num_persons] = {      //precedences
    {0, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    7
    {0, 0, 1, 1, 1, 1, 1, 1}, //Howard     7
    {1, 0, 0, 1, 1, 1, 1, 1}, //Leonard    7
    {0, 0, 0, 0, 1, 1, 1, 1}, //Stuart     5
    {0, 0, 0, 0, 0, 0, 0, 1}, //Amy        2
    {0, 0, 0, 0, 0, 0, 0, 1}, //Bernadette 2
    {0, 0, 0, 0, 0, 0, 0, 1}, //Penny      2
    {0, 0, 0, 0, 0, 0, 0, 0}  //Kripke     1
};
#define precedence_over(a,b) (prec[a->id][b->id]) // a > b
#define has_partner(a) (a->hasPartner)
#define get_parter_id(a) (a->partner->id)
#define is_girlfriend(a) (a->is_girlfriend)

bool person_comparison(Node_t *a, Node_t *b)
{   Person_t *person_a = get_person(a), *person_b = get_person(b);

    if (has_partner(person_a)> has_partner(person_a)){
        return true;
    } else if (has_partner(a) == has_partner(b){
        int precedence_a = get_person(a), precedence_b = get_person(b);
        if ( is_girlfriend(a) ) precedence_a = get_parter(a);
        if ( is_girlfriend(b) ) precedence_b = get_parter(b);
        if(precedence_over(precedence_a,precedence_a)){ // a>b
    }
    else{
        return false;
    }  
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
        persons[i].is_girlfriend = is_girlfriend[i];
        persons[i].priority_node = (Node_t *)malloc(sizeof(Node_t));
        persons[i].precedences = prec[i];
        int priority = 0;
        for (int j = 0; j < num_persons; j++)
            priority += persons[i].precedences[j];
        persons[i].priority = priority;            
        persons[i].priority_node->data = (Person_t*)(&persons[i]);
        persons[i].priority_node->comparison = person_comparison;
        persons[i].priority_node->i = priority;
        persons[i].state = WORKING;
        pthread_mutex_init(&persons[i].mutex,NULL);
    }
}
void enqueue_person(Node_t* heap[], Person_t* person) {  
    heap_insert(heap, person->priority_node);
}

Person_t*  dequeue_person(Node_t* heap[]) {
    return ( Person_t*)deleteRoot(heap, heap[0])->data;
}

Person_t* queue_first(Node_t* heap[]) {
    return ((Person_t*)(heap[0]->data));
}
// Print the heap
void print_queue(Node_t* heap[], int h_size) {
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
bool check_deadlock(Node_t* heap[]){
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
int test(int argc, char *argv[])
{
    //int h_size = 0;
    Node_t *heap[10];
    for (int i=0; i<num_persons; i++)
        heap[i]=NULL;
    
    Person_t *persons = (Person_t*) calloc(num_persons,sizeof(Person_t));
    init_persons(persons, 5);
    print_persons(persons);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[4]);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[3]);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[2]);
    print_queue(heap, num_persons);
    enqueue_person(heap, &persons[1]);
    print_queue(heap, num_persons);
     enqueue_person(heap, &persons[5]);
    print_queue(heap, num_persons);
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    enqueue_person(heap, &persons[0]);
    print_queue(heap, num_persons);
    Person_t *p = queue_first(heap); 
    printf("Max-Heap heap: %s \n", p->name );
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    p = dequeue_person(heap);
    printf("Dequeue: %s \n", p->name );
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    print_queue(heap, num_persons);
    p = dequeue_person(heap);
    printf("Dequeue: %s \n", p->name );
    print_queue(heap, num_persons);
    printf("\nDone \n");
    return 0;
}

#endif