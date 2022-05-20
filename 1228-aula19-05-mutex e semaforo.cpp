#include <stdio.h> //para funções básicas como printf e scanf
#include <stdlib.h> //outras funções padrão como rand()
#include <unistd.h> //aqui usado pelo sleep ou usleep
#include <pthread.h> //para as threads e mutex
#include <semaphore.h> //funções para os semáforos
#include <windows.h> //para a função Sleep
#include <time.h> //para a semente do srand time

//Declaro 3 semáforos um para cada thread
sem_t principal, s1, s2;
//uma variável temporária inteira para uso geral
int tmp;

//Declara e inicializa um mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Função da thread controladora
void * controladora(void * a) { //recebe um ponteiro de void
	do { //abrir um loop infinito
		printf("Controlador esperando ..\n");
		//sem_wait abre a região critica da função
		sem_wait(&principal);
		sleep(1); //para pausar o programa por 1s
		tmp = rand() % 100; //sorteia um numero entre 0 e 99
		if(tmp <= 33) { //se for menor do que 33 libera o s1
			printf("Semaforo 1 VERDE\n");
			sem_post(&s1); //semaforo 1 liberado
		} else if(tmp <= 66) { //senão se for menor que 66 libera o s2
			printf("Semaforo 2 VERDE\n");
			sem_post(&s2);//semaforo 2 liberado
		} else { //senão se for maior que 66 volta ao controlador
			printf("Semaforo 1 e 2 VERMELHO\n");
			sem_post(&principal);//controlador liberado
		}
	} while(1); //while(1) significa infinito
	pthread_exit(0); //para finalizar a thread
}
//função para o semaforo 1
void * funcao1(void * a) { //recebe um ponteiro de void
	/*cria um ponteiro de int e recebe o endereço de a
	como a é um ponteiro de void preciso convertê-lo para 
	um ponteiro de inteiro usando o 'cast' (int*) na frente do a*/
	int * valor = (int*)a;
	/*cria um inteiro chamado tmp que recebe o valor que está
	no endereço de memória de valor usando um * na frente*/
	do {//abre um loop infinito
		sem_wait(&s1); //sem_wait abre a região critica da função
		pthread_mutex_lock(&mutex);//abre a região critica com espaço compartilhado
		int tmp = * valor; //memória compartilhada entre as threads
		tmp++; //incrementa
		sleep(1);//pausa por 1s
		printf("Semaforo 1 VERMELHO %d\n",tmp);
		*valor = tmp; //*valor recebe tmp
		pthread_mutex_unlock(&mutex);//libera o mutex
		sem_post(&principal); //volta para o semáforo principal
	} while(1); //loop infinito
}
/*a função 2 é similar a 1 mas para o semáforo 2*/
void * funcao2(void * a) {
	int * valor = (int*)a;
	do {
		sem_wait(&s2);
		pthread_mutex_lock(&mutex);
		int tmp = * valor;
		tmp++;
		sleep(1);
		printf("Semaforo 2 VERMELHO %d\n",tmp);
		*valor = tmp;
		pthread_mutex_unlock(&mutex);
		sem_post(&principal);
	} while(1);
}
int main(){ //função principal do programa
	
	pthread_t thread[3]; //declaro um array de threads de 3 posições
	
	int valor = 0; //um inteiro valor com 0
	
	/*inicializo os semáforos, o principal recebe
	o terceiro parâmetro como 1 e os demais 0*/
	sem_init(&principal, 0, 1);
	sem_init(&s1, 0, 0);
	sem_init(&s2, 0, 0);
	
	/*Crio as threads com 4 parâmetros
	1 - o endereço da thread com o &
	2 - Sempre NULL
	3 - A função que será executada na thread
	4 - O endereço de uma variável que pode ser array estrutura*/
	pthread_create(&thread[0], NULL, controladora, &valor);
	pthread_create(&thread[1], NULL, funcao1, &valor);
	pthread_create(&thread[2], NULL, funcao2, &valor);
	
	/*Incluir as threads no escalonador do Sistema Operacional*/
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	
	/*é preciso destruir os semáforos depois de seu uso*/
	sem_destroy(&principal);
	sem_destroy(&s1);
	sem_destroy(&s2);
	return 0; //retorno de main;
}







