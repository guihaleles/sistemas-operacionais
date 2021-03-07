#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "tp3virtual.h"
#include "page_table.h"

// Definindo globais declaradas em tp3virtual.h e page_table.h

int faults_counter = 0;		
int dirty_counter = 0; 
char *log_file = NULL;

 
 // Array para mapear o nome do algoritmo ao nome das funcoes
int num_algs = 2;
struct replacement_alg algs[] = {
	{"rand", rand_init, rand_ref, rand_replace}, 
	{"fifo", fifo_init, fifo_ref, fifo_replace}
};

// Declarando funcoes
void (*init_function) () = NULL;
void (*ref_function) (page_table_item *) = NULL;
int (*replace_function) () = NULL;
	
// Funcao para leitura do arquivo e acessos a memoria
void execute(FILE *log) {
	printf("Executando o simulador... \n");
	
	unsigned v_addr;
	char rw;
	while (fscanf(log,"%x %c",&v_addr,&rw)==1)  {
		get_frame(v_addr, rw);
	}
	
}

// Funcao main
int main(int argc, char *argv[]) {
	
	fflush(stdout);
	fprintf(stdout, "Comecando execucao\n");
	
	int opt;
	FILE *file = stdin;
	char *replacement_alg = NULL;
	unsigned mem_size_kb = 0;
	unsigned page_size_kb = 0;
	char *usage = "USAGE: tp3virtual algorithm file page_size mem_size\n";

	while ((opt = getopt(argc, argv, "a:f:p:m:")) != -1) {
		switch (opt) {
		case 'a':
			replacement_alg = optarg;
			break;
		case 'f':
			log_file = optarg;
			break;
		case 'm':
			mem_size_kb = (unsigned) strtoul(optarg, NULL, 10);
			break;
		case 'p':
			page_size_kb = (unsigned) strtoul(optarg, NULL, 10);
			break;
		default:
			fprintf(stderr, "%s", usage);
			exit(1);
		}
	}
	if(log_file != NULL) {
		if((file = fopen(log_file, "r")) == NULL) {
			perror("Error opening log file:");
			exit(1);
		}
	}
	
	fprintf(stdout, "Argumentos lidos\n");
	fprintf(stdout, "replacement: %s\n", replacement_alg);
	fprintf(stdout, "log file: %s\n", log_file);
	fprintf(stdout, "page size kb: %d\n", page_size_kb);
	fprintf(stdout, "mem size kb: %d\n", mem_size_kb);
	
	// Initialize page_table and frames_list
	init_page_table(page_size_kb);
	init_frames_list(mem_size_kb, page_size_kb);
	
	fprintf(stdout, "Paginas inicializadas\n");

	// Inicializando funcoes do algoritmo de substituicao
	int i;
	for (i = 0; i < num_algs; i++) {
		if(strcmp(algs[i].name, replacement_alg) == 0) {
			init_function = algs[i].init;
			ref_function = algs[i].ref;
			replace_function = algs[i].replace;
			break;
		}
	}
		
	// Inicializa o algoritmo de substituicao
	init_function();

	execute(file);

	// Desaloca as estruturas
	destroy_page_table();
	destroy_frames_list();
	
	printf("Arquivo de entrada: %s\n", log_file);
	printf("Tamanho da memoria: %d KB\n", mem_size_kb);
	printf("Tamanho das páginas: %d KB\n", page_size_kb);
	printf("Tecnica de reposicao: %s\n", replacement_alg);
	printf("Paginas lidas:  %d\n", faults_counter);
	printf("Paginas escritas: %d\n", dirty_counter);

		
	return(0);
}