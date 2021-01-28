Deve ter:  
==========


- Implementar usando pthreads: 
    - mutexes (pthread_mutex_t)
    - variáveis de condição (pthread_cond_t).**

- implementar os personagens do Big Bang Theory como threads

- implementar o forno como um monitor usando pthreads, mutexes e variáveis de condição
    - Parte da solução requer o uso de uma mutex para o forno, que servirá como a trava do monitor
para as operações que os personagens podem fazer sobre ele. Além da mutex, você precisará de
um conjunto de variáveis de condição para controlar a sincronização do acesso dos casais ao
forno: uma variável para enfileirar o segundo membro de um casal se o outro já estiver
esperando, e outra variável de condição para controlar as regras de precedência no acesso direto
ao forno.

- Você deve buscar ter um código elegante e claro. Em particular, note que o comportamento dos
casais é basicamente o mesmo, você não precisa replicar o código para diferenciá-los.

- Além
disso, o comportamento de todos os personagens (exceto o Raj) é tão similar que você deve ser
capaz de usar apenas uma função para todos eles, parametrizada por um número, que identifique
cada personagem. As prioridades podem ser descritas como uma lista circular.

Regras
=======
 membros do mesmo casal esperam um atrás do outro para usar o forno;
 as regras de preferência definidas acima valem, a não ser que um casal esteja
incompleto;
 deadlock deve ser resolvido pela atuação do Raj;
 inanição deve ser evitada pela regra de voltar ao trabalho.


dependencias
==============
Consulte as páginas de manual no Linux para entender as funções da biblioteca para mutexes e
variáveis de condição:
 int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 int pthread_mutex_lock(pthread_mutex_t *mutex);
 int pthread_mutex_unlock(pthread_mutex_t *mutex); int pthread_mutex_destroy(pthread_mutex_t *mutex);
 int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
 int pthread_cond_signal(pthread_cond_t *cond);
 int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
 int pthread_cond_destroy(pthread_cond_t *cond);

Output:
========

O programa deve criar os nove personagens e receber como parâmetro o número de vezes que
eles vão tentar usar o forno:
Ao longo da execução o programa deve então mostrar mensagens sobre a evolução do processo




Caso de teste:
=================


$ ./tp1 2
Sheldon quer usar o forno
Sheldon começa a esquentar algo
Leonard quer usar o forno
Howard quer usar o forno
Amy quer usar o forno
Amy começa a esquentar algo
Sheldon vai comer
Penny quer usar o forno
Leonard começa a esquentar algo
Sheldon voltou para o trabalho
Penny começa a esquentar algo
Amy vai comer
Bernadette quer usar o forno
Kripke quer usar o forno
Amy voltou para o trabalho
Sheldon que usar o forno
Raj detectou um deadlock, liberando HowardLeonard vai comer
Penny vai comer
Howard começa a esquentar algo
Leonard voltou para o trabalho
Bernadette começa a esquentar algo
Stuart quer usar o forno
Penny voltou para o trabalho
Sheldon começa a esquentar algo
Howard vai comer
Bernadette vai comer
Sheldon vai comer
Howard voltou para o trabalho
Sheldon voltou para o trabalho
Bernadette voltou para o trabalho
Stuart começa a esquentar algo
Kripke começa a esquentar algo
Stuart vai comer
Kripke vai comer
Amy quer usar o forno
Leonard quer usar o forno
Stuart voltou para o trabalho
Leonard começa a esquentar algo
Kripke voltou para o trabalho
Leonard vai comer
Amy começa a esquentar algo