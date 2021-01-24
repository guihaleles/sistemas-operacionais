#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef enum
{
    false = 0,
    true  = 1,
} bool;

#define DETERMINISTIC true
// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
void *runner(void *param); /* os threads chamam essa função */

typedef struct Pessoa_t{
    int espera;
    char nome[20];
} Pessoa_t;

typedef struct Forno_t{
    int tempo_restante;
    bool liberado;
} Forno_t;

void monitor_microwave();
void verificar() ;
void liberar(Pessoa_t pessoa, Forno_t forno);
void esperar(Pessoa_t pessoa);
void esquentar(Pessoa_t pessoa);
void liberar(Pessoa_t pessoa, Forno_t forno);
void comer(Pessoa_t pessoa);
void acao(Pessoa_t pessoa, Forno_t forno){
int rand_int();