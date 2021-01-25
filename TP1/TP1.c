//#include "TP1.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "heap/heap.h"
#define num_persons 8

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c
//mutex 
pthread_mutex_t lock[5];

#define DETERMINISTIC true

int sum; /* esses dados são compartilhados pelo(s) thread(s) */


typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

                
/* O thread assumirá o controle nessa função */
void *runner(void *param)  /* os threads chamam essa função */
{
    int i, upper = atoi(param);
    sum = 0;
    for (i = 1; i <= upper; i++)
        sum += i;
    pthread_exit(0);
}

void monitor_microwave(Person_t pessoa)
{

// ...
 // variáveis compartilhadas, variáveis de condição
esperar(pessoa);
printf("%s quer usar o Forno_t\n", pessoa.name);

// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}

void liberar(Person_t pessoa, Forno_t forno) {
printf("%s vai comer\n", pessoa.name);
forno.liberado = true;

// ...
 // verifica se tem que liberar alguém, atualiza contadores, etc.
}

void verificar() {

// ...
 // Raj verifica se há deadlock e corrige-o
}

void esperar(Person_t pessoa){
}

void esquentar(Person_t pessoa){ /* não exige exclusão mútua */
    
}


void comer(Person_t pessoa){ // espera um certo tempo aleatório
    
}

void acao(Person_t pessoa, Forno_t forno){
    sleep(5);
    verificar(forno);
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
    
    Person_t persons[num_persons];
    init_persons(&persons);
    
                      
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
		//pthread_create(&dit[i], NULL, thr, (void *)i);
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
    
