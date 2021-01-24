//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#define num_persons 1

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock[num_persons];
pthread_cond_t cond_var[num_persons];


#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */

typedef struct Person_t{
    int espera;
    char *name;
    Node_heap_t* node_heap;
    struct Person_t* partner;
    int priority, id, idx_partner;
    Node_heap_t* priority_node;
    int *precedences;
    int numberOfUses;
} Person_t;
 



typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

// Priorities Matrix:
const char persons_names[num_persons][20] = {"Sheldon", "Howard", "Leonard", "Stuart",
                      "Penny", "Bernardette", "Amy", "Kripke"};
const int priorities[num_persons][num_persons] =  { 
                                        {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    8
                                        {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     8
                                        {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    8
                                        {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
                                        {0, 0, 0, 0, 0, 0, 0, 1}, //Amy        1 
                                        {0, 0, 0, 0, 0, 0, 0, 1}, //Bernadette 1
                                        {0, 0, 0, 0, 0, 0, 0, 1}, //Penny      1 
                                        {0, 0, 0, 0, 0, 0, 0, 0} //Kripke      0
                                };
                     
int partners[num_persons] = {    4,  //Sheldon & Amy
                    5,  //Howard & Bernadette
                    7,  //Leonard & Penny
                    -1, //Stuart
                    0,  //Amy & Sheldon
                    1,  //Bernadette & Howard
                    2,  //Penny & Leonard
                    -1  //Kripke
                };
                
bool person_comparison(Node_heap_t *a, Node_heap_t *b) {
    Person_t *person_a, *person_b;
    person_a = (Person_t*) a->data;
    person_b = (Person_t*) b->data;
    
    if   (person_a->priority > person_b->priority)
        return true;
    if(
        (person_b->priority == person_b->priority) && 
        (person_a->precedences[person_b->id] > person_b->precedences[person_a->id]) 
    ) return true;
    
    return false;
}                
void init_persons(Person_t** persons, int numberOfUses){
        for (int i=0; i<10; i++){
            persons[i]->id = i;    
            persons[i]->name = persons_names[i];
            persons[i]->idx_partner = partners[i];
            persons[i]->partner = persons[partners[i]];
            persons[i]->priority_node = (Node_heap_t*) malloc(sizeof(Node_heap_t));
            int priority = 0;
            for (int j = 0; j<num_persons; j++)
                priority+=priorities[i][j];
            persons[i]->priority_node->data = persons[i];
            persons[i]->priority_node->comparison = person_comparison;
            persons[i]->priority_node->i = priority;
            persons[i]->precedences = priorities[i];
            persons[i] ->numberOfUses = numberOfUses;
    }  
}



void *monitor_microwave(Person_t person)
{
    fprintf(stderr,"%s",person.name);

    while(person.numberOfUses){
        //do things
        //Coloca a pessoa na fila
        // wait(person);
        // pthread_mutex_lock(&lock);
        // while (a != b)
        //     pthread_cond_wait(&mutex, &cond_var);
        // pthread_mutex_unlock(&mutex);
    }


// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void release(Person_t pessoa, Forno_t forno) {
printf("%s vai comer\n", pessoa.name);
forno.liberado = true;

// ...
 // verifica se tem que liberar alguém, atualiza contadores, etc.
}


void verify() {

// ...
 // Raj verifica se há deadlock e corrige-o
}

void wait(Person_t person){
    printf("%s quer usar o Forno_t\n", person.name);
}

void heatUp(Person_t person){ /* não exige exclusão mútua */
    
}

void eat(Person_t person){ // espera um certo tempo aleatório
    
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
    fprintf(stderr,"Teste");
    Person_t persons[num_persons];
    init_persons(&persons, numberOfUses);


    

	//initialization
	for (int i; i < num_persons; i++)
	{
        fprintf(stderr,"Teste:%d ",i);
		pthread_mutex_init(&lock[i], NULL);
	}                            
                            
    /* obtém os atributos default */

	for (int i = 0; i < num_persons; i++)
	{
        pthread_attr_init(&attr);
		pthread_create(&tid[i], NULL, monitor_microwave, (void *)&persons[i]);
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
    
