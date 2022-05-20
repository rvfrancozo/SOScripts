#include <stdio.h> //usado para fun��es b�sicas como printf e scanf
#include <stdlib.h> //usado para a fun��o rand() e srand()
#include <unistd.h> //� usado para a fun��o sleep e usleep
#include <windows.h> //me d� a fun��o Sleep s� para windows
#include <time.h> //� usado para a fun��o time() para o srand
#include <pthread.h> //das threads e mutex
#include <semaphore.h> //para os sem�foros

/*crio 3 sem�foros para ser usado no programa*/
sem_t principal, s1, s2; //sem_t tipo de sem�foro
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*crio a fun��o do controlador*/
void * controlador(void * a) { //recebe um ponteiro de void chamado a
	do { //abre um loop infinito
		printf("Controlador ...\n");
		//Sinaliza o sem�foro principal - entra na regi�o cr�tica
		sem_wait(&principal);//abre a minha regi�o cr�tica
		sleep(1); //pausa por 1 segundo
		int tmp = rand() % 100; //escolhe um valor aleat�rio entre 0 e 99
		if(tmp <= 33) { //se tmp for menor ou igual a 33
			printf("Semaforo 1 VERDE\n");
			sem_post(&s1); //abre o semaforo para s1
		} else if (tmp <= 66) {//sen�o se tmp for menor ou igual a 66
			printf("Semaforo 2 VERDE\n");
			sem_post(&s2);//abre o semaforo para s2
		} else { //sen�o tmp � maior que 66
			printf("Semaforo 1 e 2 VERMELHO\n");
			sem_post(&principal);//volta para o controlador
		}
	} while(1); //while(1) informa que o loop � infinito
}
//Cria a fun��o do sem�foro 1
void * funcao1(void * a) {
	/*converte o 'a' de ponteiro de void para ponteiro de inteiro
	e atribui ao ponteiro de inteiro chamado valor*/
	int * valor = (int*)a; 
	
	do {//loop infinito
		sem_wait(&s1);//abre o sem�foro1
		/*d� um lock no mutex para trabalhar com a vari�vel compartilhada
		dentro da regi�o critica*/
		pthread_mutex_lock(&mutex); 
		int tmp = *valor; //cria uma vari�vel tmp para receber esse valor
		tmp++;//incrementa o tmp
		sleep(1); //pausa por 1 segundo
		printf("Semaforo 1 VERMELHO %d:\n",tmp);
		*valor = tmp; //devolve o tmp para a mem�ria
		pthread_mutex_unlock(&mutex);
		sem_post(&principal);//volta para o controlador
	} while(1);
}
//essa fun��o � igual a funcao1 mas para o s2
void * funcao2(void * a) {
	int * valor = (int*)a;
	do {
		sem_wait(&s2);
		pthread_mutex_lock(&mutex); 
		int tmp = *valor;
		tmp++;
		sleep(1);
		printf("Semaforo 1 VERMELHO: %d\n",tmp);
		*valor = tmp;
		pthread_mutex_unlock(&mutex);
		sem_post(&principal);
	} while(1);
}
//fun��o main principal
int main() {
	pthread_t thread[3];//crio um array de threads com 3 posi��es
	
	int dado = 0;//cria e inicializa um inteiro dado com valor 0
	
	/*Inicializa os sem�foros com 3 par�metros cada, o primeiro 
	par�metro � o endere�o do sem�foro (com o &) o segundo � 
	sempre 0, o terceiro � 1 para o sem�foro principal e 0 para 
	os demais*/
	sem_init(&principal, 0 , 1);
	sem_init(&s1, 0 , 0);
	sem_init(&s2, 0 , 0);
	
	/*Crio as threads com 4 par�metros, o primeiro � o endere�o da
	thread, o segundo par�metro � sempre NULL, o terceiro � a fun��o
	que a thread vai executar e o quarto � um par�metro que pode ser
	o endere�o de mem�ria de vari�vel, um array, uma estrutura etc
	que na fun��o � recebido como um ponteiro de void*/
	pthread_create(&thread[0],NULL,controlador,NULL);
	pthread_create(&thread[1],NULL,funcao1,&dado);
	pthread_create(&thread[2],NULL,funcao2,&dado);
	
	/*Adiciona as threads criadas no escalonador do sistema operacional*/
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	
	/*Destroy os sem�foros*/
	sem_destroy(&principal);
	sem_destroy(&s1);
	sem_destroy(&s2);
	
	return 0; //retorno de main
}











