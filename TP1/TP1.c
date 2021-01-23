#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Comando que estou usando para compilar:
// gcc -pthread -o TP1 TP1.c

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
void *runner(void *param); /* os threads chamam essa função */
int main(int argc, char *argv[])
{

    pthread_t tid; /* o identificador do thread */
    pthread_attr_t attr; /* conjunto de atributos do thread */

    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    
    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
        return -1;
    }
    
    /* obtém os atributos default */
    pthread_attr_init(&attr);

    /* cria o thread */
    pthread_create(&tid,&attr,runner,argv[1]);

    /* espera o thread ser encerrado */
    pthread_join(tid,NULL);
    printf("sum = %d\n",sum);
}
    
/* O thread assumirá o controle nessa função */
void *runner(void *param)
{
    int i, upper = atoi(param);
    sum = 0;
    for (i = 1; i <= upper; i++)
        sum += i;
    pthread_exit(0);
}




void monitor_microwave()
{
... // variáveis compartilhadas, variáveis de condição
esperar(personagem pessoa) {
printf("%s quer usar o Forno_t\n", nome(b.num));
... // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void liberar(personagem pessoa) {
printf("%s vai comer\n", nome(b.num));
... // verifica se tem que liberar alguém, atualiza contadores, etc.
}


verificar() {
... // Raj verifica se há deadlock e corrige-o
}


typedef struct Pessoa_t
{
};

typedef struct Forno_t
{
};

void esperar(Pessoa_t pessoa){
    drand48()
}

void esquentar(Pessoa_t pessoa){ /* não exige exclusão mútua */
    
}


void liberar(Pessoa_t pessoa, Forno_t forno){
    
}


void comer(Pessoa_t pessoa){ // espera um certo tempo aleatório
    
}

void acao(Pessoa_t pessoa){
    sleep(5);
    verificar(Forno_t);
}