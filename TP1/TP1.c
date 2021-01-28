//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#include "Person.c"
#define num_persons 5

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
    
    while(person.numberOfUses >= 1){

        wait(&person, i);

        generateNext(i);
 
        heatUp(&person);

        eat(&person);

        work(&person);        
    }
}


void eat(Person_t *person) {
    // ver se tem aguem para liberar na fila
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&lock);
    (person->numberOfUses)--;
    printf("%s vai comer\n",  person->name);

}

generateNext(int i){
        // printf("Working Thread:%d \n",i);
        if(nextThread == num_persons-1)
        {            
            nextThread = 0;
        }
        else
        {
            nextThread++;
        }
        // printf("Next Thread:%d \n",nextThread);
}

work(Person_t *person){
     printf("%s voltou para o trabalho\n",person->name);
     sleep(rand_int());
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
    //coloca na fila aqui!
    while (nextThread != i)
    {
        pthread_cond_wait(&cond_var, &lock);
    }
}

void heatUp(Person_t *person){
    printf("%s começa a esquentar algo\n", person->name);
    sleep(1);
}

int rand_int(){
    int ret;
    if (DETERMINISTIC == false)
        ret = (int) ((3*drand48())+3);
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
    
