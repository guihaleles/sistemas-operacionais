 
# Geral

O simulador receberá como entrada um arquivo que conterá a sequência de
endereços de memória acessados por um programa

Esses endereços estarão escritos como números hexadecimais, seguidos por uma letra R ou W,
para indicar se o acesso foi de leitura ou escrita

Ao iniciar o programa, será definido o tamanho da memória (em quadros) para aquele programa e qual o
algoritmo de substituição de páginas a ser utilizado.

O programa deve, então, processar cada acesso à memória para atualizar os bits de controle de cada
quadro, detectar falhas de páginas (page faults) e simular o processo de carga e substituição de páginas.

Durante todo esse processo, estatı́sticas devem ser coletadas, para gerar um relatório ao final da execução.



tp2virtual, deverá ser iniciado com quatro argumentos: tp2virtual [algoritmo] arquivo.log 4 128


os algoritmos de substituição que devem ser utilizados (lru, 2a – segunda
chance –, fifo e um novo algoritmo implementado pelo aluno e ser diferente
dos algoritmos de substituição já existentes)