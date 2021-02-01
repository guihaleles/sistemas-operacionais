//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Person.c"
#define num_persons 8

/* esses dados são compartilhados pelo(s) thread(s) */
pthread_mutex_t lock;
pthread_cond_t cond_var[num_persons];

#define DETERMINISTIC false
int monitor_queue[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int nextThread = -1; 
bool end = false;

Person_t persons[num_persons];
Node_t heap[num_persons];
/*--------------------------------------------------*/

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

    dequeue_person(heap);
    // printf("\n");
    // print_queue(heap,num_persons);
    // printf("\n");

    if(heap[0].data != NULL && !check_deadlock(heap)){

        // printf("Entrou!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        
        Person_t *p = queue_first(heap);
        nextThread = p->id;

        // printf("NextThread eat: %d\n", nextThread);
        // printf("NextThread eat: %s\n", p->name);

        pthread_cond_signal(&cond_var[nextThread]);

    }

    pthread_mutex_unlock(&lock);
    
    (person->numberOfUses)--;
    
    printf("%s vai comer\n",  person->name);

}

void work(Person_t *person){
     printf("%s voltou para o trabalho\n",person->name);
     sleep(rand_int());
}


void *thr_raj(){
    
    Person_t* person;
    while(!end)
    {

        if(check_deadlock(heap)){
            person = queue_first(heap);
            // print_queue(heap,num_persons);
            nextThread = person->id;
            pthread_cond_signal(&cond_var[nextThread]);
            printf("Raj detectou um deadlock, liberando %s\n", person->name);    
        }

        sleep(5);
    }
   

}

void wait_to_use_oven(Person_t *person, int i){


    enqueue_person(heap,person);
    printf("%s quer usar o Forno\n", person->name);
    // printf("\n");
    // print_queue(heap,num_persons);
    // printf("\n");

    Person_t *p = queue_first(heap);
    nextThread = p->id;

    pthread_mutex_lock(&lock);
    // printf("NextThread: %d\n", nextThread);
    // printf("thread queue:%d\n", i);   

    while (nextThread != i)
    {
        pthread_cond_wait(&cond_var[i], &lock);
        // printf("NextThread: %d\n", nextThread);
        // printf("thread cond:%d\n", i);
    }
    // printf("------\n");
    // printf("%s assumiu o controle\n", person->name);
    // printf("------\n");
}

void heatUp(Person_t *person){
    printf("%s começa a esquentar algo\n", person->name);
    sleep(1);
}


void *thr_person(void *arg)
{
    int i= (int)arg;
    Person_t person = persons[i];
    
    while(person.numberOfUses >= 1){        

        wait_to_use_oven(&person, i);

        heatUp(&person);

        eat(&person);

        work(&person);        
    }
    // print_queue(heap,num_persons);
    // printf("%s finalizou\n",person.name);k
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
        // printf("Thread create:%d ",i);
        // printf("Thread create:%s ",persons[i].name);
        // printf("Thread create:%d \n",persons[i].id);
	}
        
    pthread_create(&tid_raj,NULL,thr_raj,NULL);  

	//Recycle thread
	for (int i = 0; i < num_persons; i++)
	{
		pthread_join(tid[i], NULL);
	}
    printf("finalizou\n");
    end = true;

    pthread_join(&tid_raj,NULL);
	//Destruction
	pthread_exit(NULL);

	return 0;
}
    
