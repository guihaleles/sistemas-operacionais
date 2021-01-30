//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Person.c"
#include "Queue.c"
#define num_persons 8

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock;
pthread_cond_t cond_var;

#define DETERMINISTIC false

int nextThread = -1; /* esses dados são compartilhados pelo(s) thread(s) */

Person_t persons[num_persons];
Node_t heap[num_persons];


int rand_int(){
    int ret;
    if (DETERMINISTIC == false)
        ret = (int) ((3*drand48())+3);
    else 
        ret= 2;
    return ret;
}



void eat(Person_t *person) {
    // ver se tem aguem para liberar na fila

    deQueue(person->id);
    nextThread = getHighestScoreId();
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&lock);
    (person->numberOfUses)--;
    printf("%s vai comer\n",  person->name);

}

void generateNext(){
        printf("Working Thread:%d \n",nextThread);
        if(nextThread == num_persons-1)
        {            
            nextThread = 0;
        }
        else
        {
            nextThread++;
        }
        printf("Next Thread:%d \n",nextThread);
}

void work(Person_t *person){
     printf("%s voltou para o trabalho\n",person->name);
     sleep(rand_int());
}


void *thr_raj(){
    printf("raj\n");

    if(nextThread==-1){
        deQueue((int)(position*drand48()));
    }

    sleep(5);
}

void wait_to_use_oven(Person_t *person, int i){
    
    printf("%s quer usar o Forno\n", person->name);
    pthread_cond_wait(person->mutex)
    nextThread = getHighestScoreId();
    pthread_mutex_lock(&lock);    
    while (nextThread != i)
    {
        printf("NextThread: %d\n", nextThread);
        pthread_cond_wait(&cond_var, &lock);
    }
}

void heatUp(Person_t *person){
    printf("%s começa a esquentar algo\n", person->name);
}


void *thr_person(void *arg)
{
    int i= (int)arg;
    Person_t person = persons[i];
    
    while(persons[i]->numberOfUses >= 1){        

        wait_to_use_oven(persons[i], i);
        //generateNext();
        heatUp(persons[i]);

        eat(persons[i]);

        work(persons[i]);        
    }
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
		pthread_create(&tid[i], NULL, thr_person, (void *)i);
        printf("Thread create:%d \n",i);
	}
        
    pthread_create(&tid_raj,NULL,thr_raj,NULL);  

	//Recycle thread
	for (int i = 0; i < num_persons; i++)
	{
		pthread_join(tid[i], NULL);
	}

    pthread_join(&tid_raj,NULL);
	//Destruction
	pthread_exit(NULL);

	return 0;
}
    
