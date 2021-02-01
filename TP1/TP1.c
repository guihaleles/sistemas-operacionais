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

int nextThread = -1; 
bool end = false;

Person_t persons[num_persons];
Node_t heap[num_persons];
/*--------------------------------------------------*/


//Função que retorna um valor aleatório entre 3 e 6 ou quando não deterministico
int rand_int(){
    int ret;
    if (DETERMINISTIC == false)
        ret = (int) ((3*drand48())+3);
    else 
        ret= 2;
    return ret;
}

//Retira a thread atual da fila e define qual a pŕoxma thread da fila deve utilizar o recurso
void eat(Person_t *person) {

    dequeue_person(heap);

    if(heap[0].data != NULL && !check_deadlock(heap)){
        
        Person_t *p = queue_first(heap);
        nextThread = p->id;

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

//Thread Raj, que monitora o deadlock  
void *thr_raj(){
    
    Person_t* person;
    while(!end)
    {
        if(check_deadlock(heap)){
            person = queue_first(heap);
            nextThread = person->id;
            pthread_cond_signal(&cond_var[nextThread]);
            printf("Raj detectou um deadlock, liberando %s\n", person->name);    
        }
        sleep(5);
    }
}

//insere a thread atual na fila e espera um sinal caso o recurso compartilhado não esteja disponível
void wait_to_use_oven(Person_t *person, int i){

    enqueue_person(heap,person);
    printf("%s quer usar o Forno\n", person->name);

    Person_t *p = queue_first(heap);
    nextThread = p->id;

    pthread_mutex_lock(&lock);  

    while (nextThread != i)
    {
        pthread_cond_wait(&cond_var[i], &lock);
    }

}

void heatUp(Person_t *person){
    printf("%s começa a esquentar algo\n", person->name);
    sleep(1);
}

//Thread princiapl
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

    //Número de veses em que os persongens utilizaram o forno
    int numberOfUses = atoi(argv[1]);

    /* o identificador da threads */
    pthread_t tid[num_persons]; 

    pthread_t tid_raj;

    //Inicialia os personagens
    init_persons(&persons, numberOfUses);

    pthread_cond_init(&cond_var,NULL);
    

	//inicialização das mutex
	pthread_mutex_init(&lock, NULL);

	for (int i = 0; i < num_persons; i++)
	{
		pthread_create(&tid[i], NULL, thr_person, (void *)i);

	}
        
    pthread_create(&tid_raj,NULL,thr_raj,NULL);  

	//Recycle thread
	for (int i = 0; i < num_persons; i++)
	{
		pthread_join(tid[i], NULL);
	}

    end = true;

    pthread_join(&tid_raj,NULL);
	
    //Destruction
	pthread_exit(NULL);

	return 0;
}
    
