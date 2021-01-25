//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#define num_persons 2

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock[num_persons];
pthread_cond_t cond_var[num_persons];

#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */


// typedef struct Person_t{
//     int espera;
//     char *name;
//     int numberOfUses;
// } Person_t;

typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

Person_t persons[num_persons];

// // Priorities Matrix:
// const char persons_names[num_persons][20] = {"Sheldon", "Howard", "Leonard", "Stuart",
//                       "Penny", "Bernardette", "Amy", "Kripke"};
// const int priorities[num_persons][num_persons] =  { 
//                                         {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    8
//                                         {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     8
//                                         {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    8
//                                         {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
//                                         {0, 0, 0, 0, 0, 0, 0, 1}, //Amy        1 
//                                         {0, 0, 0, 0, 0, 0, 0, 1}, //Bernadette 1
//                                         {0, 0, 0, 0, 0, 0, 0, 1}, //Penny      1 
//                                         {0, 0, 0, 0, 0, 0, 0, 0} //Kripke      0
//                                 };
                     
// int partners[num_persons] = {    4,  //Sheldon & Amy
//                     5,  //Howard & Bernadette
//                     7,  //Leonard & Penny
//                     -1, //Stuart
//                     0,  //Amy & Sheldon
//                     1,  //Bernadette & Howard
//                     2,  //Penny & Leonard
//                     -1  //Kripke
//                 };
                
// // bool person_comparison(Node_heap_t *a, Node_heap_t *b) {
// //     Person_t *person_a, *person_b;
// //     person_a = (Person_t*) a->data;
// //     person_b = (Person_t*) b->data;
    
// //     if   (person_a->priority > person_b->priority)
// //         return true;
// //     if(
// //         (person_b->priority == person_b->priority) && 
// //         (person_a->precedences[person_b->id] > person_b->precedences[person_a->id]) 
// //     ) return true;
    
// //     return false;
// // } 

// // void init_persons(Person_t** persons, int numberOfUses){
// //         fprintf(stderr,"Teste");
// //         for (int i=0; i<num_persons; i++){
// //             persons[i]->id = i;    
// //             persons[i]->name = persons_names[i];
// //             persons[i]->idx_partner = partners[i];
// //             persons[i]->partner = persons[partners[i]];
// //             persons[i]->priority_node = (Node_heap_t*) malloc(sizeof(Node_heap_t));
// //             int priority = 0;
// //             for (int j = 0; j<num_persons; j++){
// //                  priority+=priorities[i][j];
// //             }
// //             persons[i]->priority_node->data = persons[i];
// //             persons[i]->priority_node->comparison = person_comparison;
// //             persons[i]->priority_node->i = priority;
// //             persons[i]->precedences = priorities[i];
// //             persons[i] ->numberOfUses = numberOfUses;
// //     }  p
// // }

// void init_persons(Person_t person[num_persons],int numberOfUses){
//     for(int i=0; i<num_persons; i++){
//         person[i].name = persons_names[i];
//         person[i].espera = i;
//         person[i].numberOfUses = numberOfUses;
//         fprintf(stderr,"NomePerson:%s ",persons_names[i]);
//     }    
// }

void *monitor_microwave(void *arg)
{
    int i= (int)arg;
    Person_t person = persons[i];

    while(person.numberOfUses >= 1){
        //do things
        //Coloca a pessoa na fila
        wait(person);

        // while (a != b)
        verify();
        heatUp(person);
        release(&person);
        // printf("%d", person.numberOfUses);
        eat(person);

        // pthread_mutex_unlock(&mutex);
        
    }


// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void release(Person_t *person) {
    pthread_mutex_unlock(&lock);
    // printf("%d", person.numberOfUses);
    (person->numberOfUses)--;
    sleep(1);
// ...
 // verifica se tem que liberar alguém, atualiza contadores, etc.
}


void verify() {

// ...
 // Raj verifica se há deadlock e corrige-o
}

void wait(Person_t person){
    printf("%s quer usar o Forno\n", person.name);
    //coloca na fila
}

void heatUp(Person_t person){
    if(pthread_mutex_lock(&lock) == 0){
        printf("%s começa a esquentar algo\n", person.name);
        sleep(1);
    }
}

void eat(Person_t person){
    printf("%s vai comer\n", person.name);
}

void action(Person_t person, Forno_t forno){
    sleep(5);
    verify(forno);
}


int rand_int(){
    int ret;
    if (DETERMINISTIC == false)
        ret = (int) 100*drand48();
    else 
        ret= 2;
    return ret;
}

// FIFO


// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
//void *runner(void *param); /* os threads chamam essa função */
int main(int argc, char *argv[])
{


    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    
    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
        return -1;
    }

    int numberOfUses = atoi(argv[1]);

    
    pthread_t tid[num_persons]; /* o identificador do thread */
    pthread_attr_t attr[num_persons]; /* conjunto de atributos do thread */

    init_persons(&persons, numberOfUses);
    

	//initialization
	for (int i = 0; i < num_persons; i++)
	{
		pthread_mutex_init(&lock[i], NULL);
	}                            
                            
    /* obtém os atributos default */

	for (int i = 0; i < num_persons; i++)
	{
        pthread_attr_init(&attr);
		pthread_create(&tid[i], NULL, monitor_microwave, (void *)i);
	}

	//Recycle thread
	for (int i = 0; i < num_persons; i++)
	{
		pthread_join(tid[i], NULL);
	}
	//Destruction
	pthread_exit(NULL);

	return 0;
}
    
