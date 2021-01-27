//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#include "Person.c"
#define num_persons 3

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock;
pthread_cond_t cond_var;

#define DETERMINISTIC false

int nextThread = 0; /* esses dados são compartilhados pelo(s) thread(s) */


typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

Person_t persons[num_persons];

void *monitor_microwave(void *arg)
{
    int i= (int)arg;
    Person_t person = persons[i];
    sleep(1);
    while(1){

        // pthread_mutex_lock(&lock);
        // printf("Lock Thread:%d \n",i);
        // //coloca na fila
        // while (nextThread != i)
        // {
        //     printf("Cond Thread:%d ",i);
        //     printf("/ Next:%d \n",nextThread);
        //     pthread_cond_wait(&cond_var, &lock);
        // }
        wait(&person, i);

        printf("Working Thread:%d \n",i);
        if(nextThread == num_persons-1)
        {            
            nextThread = 0;
        }

        else
        {
            nextThread++;
        }
        printf("Next Thread:%d \n",nextThread);
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&lock);
        sleep(rand_int());
        
    }


// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void release(Person_t *person) {
    pthread_mutex_unlock(&lock);
    (person->numberOfUses)--;
    person->released = false;
    sleep(1);
// ...
 // verifica se tem que liberar alguém, atualiza contadores, etc.
}


void verify() {

// ...
 // Raj verifica se há deadlock e corrige-o
}

void *raj(){
    printf("raj\n");
    for (int i = 0; i < num_persons; i++)
	{
        printf("raj %d\n",i);
        persons[i].released = true;
        sleep(5);
    }
}

void wait(Person_t *person, int i){
    pthread_mutex_lock(&lock);
    printf("%s quer usar o Forno\n", person->name);
    while (nextThread != i)
        {
            // printf("Cond Thread:%d ",i);
            // printf("/ Next:%d \n",nextThread);
            pthread_cond_wait(&cond_var, &lock);
        }
}

void heatUp(Person_t *person){
    printf("%s quer usar o Forno\n", person->name);
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
        ret = (int) 5*drand48();
    else 
        ret= 2;
    return ret;
}



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

    pthread_t tid_raj;

    init_persons(&persons, numberOfUses);
    pthread_cond_init(&cond_var,NULL);
    

	//initialization
	pthread_mutex_init(&lock, NULL);
                           
                
    /* obtém os atributos default */

	for (int i = 0; i < num_persons; i++)
	{
		pthread_create(&tid[i], NULL, monitor_microwave, (void *)i);
        printf("Thread create:%d \n",i);
	}
        
    // pthread_create(&tid_raj,NULL,raj,NULL);  

	//Recycle thread
	for (int i = 0; i < num_persons; i++)
	{
		pthread_join(tid[i], NULL);
	}
	//Destruction
	pthread_exit(NULL);

	return 0;
}
    
