//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#include "Person.c"
#define num_persons 2

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock[num_persons];
pthread_cond_t cond_var[num_persons];

#define DETERMINISTIC true


typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

Person_t persons[num_persons];

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
        printf("%d", person.numberOfUses);
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
        fprintf(stderr,"Nome: %s \n",persons[i].name);
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
    
