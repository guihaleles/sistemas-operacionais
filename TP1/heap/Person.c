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

#define get_person(x) ((Person_t*)x->data) // get person from node
#define DETERMINISTIC true
#define NUM_PERSONS  8
#define max_name_len 20

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
    bool partner_in_line;
    bool is_girlfriend;
} Person_t;
// Priorities Matrix:

char persons_names[NUM_PERSONS][max_name_len] = {"Sheldon", "Howard", "Leonard", "Stuart",
                                              "Amy","Bernardette","Penny",  "Kripke"};
int is_girlfriend[NUM_PERSONS] = {false, false, false, false, true, true, true, false};
int num_persons = NUM_PERSONS;

int partners[NUM_PERSONS] = {
    4,  //Sheldon & Amy
    5,  //Howard & Bernadette
    6,  //Leonard & Penny
    -1, //Stuart
    0,  //Amy & Sheldon
    1,  //Bernadette & Howard
    2,  //Penny & Leonard
    -1  //Kripke
};
int prec[NUM_PERSONS][NUM_PERSONS] = {      //precedences
    {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    7
    {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     7
    {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    7
    {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
    {0, 0, 0, 0, 1, 0, 0, 1}, //Amy        2
    {0, 0, 0, 0, 0, 1, 0, 1}, //Bernadette 2
    {0, 0, 0, 0, 0, 0, 1, 1}, //Penny      2
    {0, 0, 0, 0, 0, 0, 0, 1}  //Kripke     1
};
#define precedence_over(a,b) (prec[a->id][b->id]) // a > b
#define has_partner(a) (a->has_partner)
#define get_parter_id(a) (a->partner->id)
#define is_girlfriend(a) (a->is_girlfriend)

bool person_comparison(Node_t *a, Node_t *b)
{   
    Person_t *person_a = get_person(a), *person_b = get_person(b);

    if (person_a->partner_in_line > person_b->partner_in_line)
        return true;
    if (person_a->partner_in_line == person_b->partner_in_line){
        Person_t *precedence_a = person_a;
        Person_t *precedence_b = person_b;
        if ( person_a->partner_in_line && person_a->is_girlfriend ) 
            precedence_a = person_a->partner;
        if ( person_a->partner_in_line && person_b->is_girlfriend )
             precedence_b = person_b->partner;
        if(precedence_over(precedence_a,precedence_b) > precedence_over(precedence_b,precedence_a)) // a>b
            return true;
        if (precedence_over(precedence_a,precedence_b) == precedence_over(precedence_b,precedence_a)){
            if(person_b->is_girlfriend)
                return true;
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
        persons[i].partner = &(persons[partners[i]]);
        persons[i].is_girlfriend = is_girlfriend[i];
        persons[i].partner_in_line = false;
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
    for(int i=0; heap[i] != NULL; i++){
        if (get_person(heap[i]) == person->partner){
            person->partner_in_line = true;
            person->partner->partner_in_line = true;
            if (get_person(heap[i])->is_girlfriend)
                heap[i]->data = (void*) person;         
            printf("Enqueue: %s, partner %s found!\n", person->name, person->partner->name);
        }
    }
    if (person->partner_in_line == false){   
        heap_insert(heap, person->priority_node);
        printf("Enqueue: %s\n", person->name);
        print_queue(heap, num_persons);
    }

}

Person_t*  dequeue_person(Node_t* heap[]) {
    Person_t* person= ( Person_t*)heap[0]->data;
    if (person->partner->partner_in_line == false){
        deleteRoot(heap, heap[0]);
        person->partner->partner_in_line = false;
    } else{
        heap[0]->data = ( void*) person->partner;
        person->partner_in_line = false;
    }
    printf("Dequeue %s\n", person->name);
    print_queue(heap, num_persons);
    return person;
    
}

Person_t* queue_first(Node_t* heap[]) {
    return ((Person_t*)(heap[0]->data));
    print_queue(heap, num_persons);

}
// Print the heap
void print_queue(Node_t* heap[], int h_size) {
  for (int i = 0; i < h_size; ++i)
    if (heap[i] != NULL){
        printf("%s ", ((Person_t*)(heap[i]->data))->name);
        if( ((Person_t*)(heap[i]->data))->partner_in_line 
            && ((Person_t*)(heap[i]->data))->partner->partner_in_line)
            printf("- %s     ", ((Person_t*)(heap[i]->data))->partner->name);
    }
  printf("\n");
}


void update_queue(Node_t* heap[]){
    for (int i = h_size / 2 - 1; i >= 0; i--)
        heapify(heap, h_size, i);
    print_queue(heap, num_persons);

        
}
bool check_deadlock(Node_t* heap[]){
    //Return true if there is a deadlock
    int ids_before[h_size];
    for(int i=0; i<h_size;i++)
        ids_before[i] = get_person(heap[i])->id;
    update_queue(heap);
    for(int i=0; i<h_size;i++)
        if (ids_before[i] != get_person(heap[i])->id)
            return true;
    return false;    
}

void print_persons(Person_t persons[]) {
  for (int i = 0; i < num_persons; i++){
        printf("%s ",persons[i].name);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
    //int h_size = 0;
    Node_t *heap[10];
    for (int i=0; i<num_persons; i++)
        heap[i]=NULL;
    
    Person_t *persons = (Person_t*) calloc(num_persons,sizeof(Person_t));
    init_persons(persons, num_persons);
    print_queue(heap, num_persons);
    print_persons(persons);
    enqueue_person(heap, &persons[4]);
    enqueue_person(heap, &persons[3]);
    enqueue_person(heap, &persons[2]);
    enqueue_person(heap, &persons[1]);
     enqueue_person(heap, &persons[5]);
    enqueue_person(heap, &persons[0]);
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    printf("Max-Heap heap: %s \n", queue_first(heap)->name );
    enqueue_person(heap, &persons[6]);
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    dequeue_person(heap);
    if (check_deadlock(heap))
        printf("Deadlock!!!\n");
    dequeue_person(heap);
    printf("\nDone \n");
    return 0;
}

#endif