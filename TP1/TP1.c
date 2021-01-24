#include "TP1.h"

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




void monitor_microwave(Pessoa_t pessoa)
{

// ...
 // variáveis compartilhadas, variáveis de condição
esperar(pessoa);
printf("%s quer usar o Forno_t\n", pessoa.nome);

// ...
 // verifica quem mais quer usar, contadores, variáveis de cond., etc.
}


void liberar(Pessoa_t pessoa, Forno_t forno) {
printf("%s vai comer\n", pessoa.nome);

// ...
 // verifica se tem que liberar alguém, atualiza contadores, etc.
}


void verificar() {

// ...
 // Raj verifica se há deadlock e corrige-o
}

void esperar(Pessoa_t pessoa){
}

void esquentar(Pessoa_t pessoa){ /* não exige exclusão mútua */
    
}


void liberar(Pessoa_t pessoa, Forno_t forno){
    forno.liberado = true;
}


void comer(Pessoa_t pessoa){ // espera um certo tempo aleatório
    
}

void acao(Pessoa_t pessoa, Forno_t forno){
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