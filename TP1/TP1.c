//#include "TP1.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
// #include "heap/heap.h"
// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock[5];
pthread_cond_t cond_var[5];

typedef enum
{
    false = 0,
    true  = 1,
} bool;

#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */

typedef struct Person_t{
    int wait;
    char name[20];
    // Node_heap_t* node_heap;
    Person_t* partner;
    int priority;
} Person_t;

typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

Person_t *people;

char names_persons[] = {"Sheldon", "Howard", "Leonard", "Stuart", "Penny", "Bernardette", "Amy", "Raj", "Kripke"};
//Matrix de priorities:
int priorities[] =  { {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon     8
                        {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     8
                        {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    8
                        {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
                        {0, 0, 0, 0, 0, 0, 0, 1}, //Amy        1 
                        {0, 0, 0, 0, 0, 0, 0, 1}, //Bernadette 1
                        {0, 0, 0, 0, 0, 0, 0, 1}, //Raj        1 
                        {0, 0, 0, 0, 0, 0, 0, 1}, //Penny      1 
                        {0, 0, 0, 0, 0, 0, 0, 0} //Kripke      0
};
                     
int partners = {   4, //Sheldon & Amy
                    5, //Howard & Bernadette
                    7, //Leonard & Penny
                    -1, //Stuart
                    7, //Amy & Sheldon
                    7, //Bernadette & Howard
                    -1, //Raj
                    7, //Penny & Leonard
                    -1 //Kripke
                };
                
// bool comparison(Node_heap_t *a, Node_heap_t *b) {
//     if   (a->data.priority > b->data.priority)
//         return true;
//     else if(a->data.priority = b->data.priority){
//         if (a->data.precedencia[b->data.id] > b->data.precedencia[a->data.id]){
//             return true;
//         } else {
//             return false;
//         }
        
//     }
// }   

// void init_persons(Person_t ** persons){
//         for (int i=0; i<10; i++){
//         persons[i].id = i;    
//         persons[i].name = names_persons[i];
//         persons[i].idx_partner = partners[i];
//         persons[i].partner = persons[partners[i]];
//         persons[i].priority_node = (Node_heap_t*) malloc(sizeof(Node_heap_t));
//         int priority =0;
//         for (int j =0, j<num_persons, j++)
//             priority+=priorities[i][j];
//         persons[i].priority_node.data = persons[i];
//         persons[i].priority_node.comparison = comparison;
//         persons[i].priority_node->i = priority;
//         persons[i].precedencias=priorities[i];
//     }  
// }

void init_persons(int number){
    people = (int *)malloc(number * sizeof(Person_t));

    for( int i =0; i<number; i++){
        Person_t item = {
            0,
            names_persons[i],
            NULL,
            priorities[i]
        };
        people[i] = item;
        printf("%s", people[i].name);
    }
}


// /* O thread assumirá o controle nessa função */
// void *runner(void *param)  /* os threads chamam essa função */
// {
//     int i, upper = atoi(param);
//     sum = 0;
//     for (i = 1; i <= upper; i++)
//         sum += i;
//     pthread_exit(0);
// }


void *monitor_microwave(Person_t person)
{

//Coloca a pessoa na fila
wait(person);
pthread_mutex_lock(&lock);

while (a != b)
    pthread_cond_wait(&mutex, &cond_var);
pthread_mutex_unlock(&mutex);


// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void release(Person_t person, Forno_t forno) {
printf("%s vai comer\n", person.name);

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


void release(Person_t person, Forno_t forno){
    forno.liberado = true;
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
    int num_vezes_forno = atoi(argv[1]);
    
    pthread_t tid[5]; /* o identificador do thread */
    pthread_attr_t attr[5]; /* conjunto de atributos do thread */
    
    // Person_t persons[num_persons];
    init_persons(5);
    
                      
	//initialization
	for (int i; i < 5; i++)
	{
		pthread_mutex_init(&lock[i], NULL);
	}                            
                            
    /* obtém os atributos default */

	//Create thread
	pthread_t dit[5];
	for (int i = 0; i < 5; i++)
	{
        pthread_attr_init(&attr);
		pthread_create(&dit[i], NULL, monitor_microwave, (void *)i);
	}

	//Recycle thread
	for (int i = 0; i < 5; i++)
	{
		pthread_join(dit[i], NULL);
	}
	//Destruction
	pthread_exit(NULL);

	return 0;
}
    
