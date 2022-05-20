#include <stdio.h> //usado para funções básicas como printf e scanf
#include <stdlib.h> //usado para a função rand() e srand()
#include <unistd.h> //é usado para a função sleep e usleep
#include <windows.h> //me dá a função Sleep só para windows
#include <time.h> //é usado para a função time() para o srand
#include <pthread.h> //das threads e mutex
#include <semaphore.h> //para os semáforos

/*crio 3 semáforos para ser usado no programa*/
sem_t principal, s1, s2; //sem_t tipo de semáforo
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*crio a função do controlador*/
void * controlador(void * a) { //recebe um ponteiro de void chamado a
	do { //abre um loop infinito
		printf("Controlador ...\n");
		//Sinaliza o semáforo principal - entra na região crítica
		sem_wait(&principal);//abre a minha região crítica
		sleep(1); //pausa por 1 segundo
		int tmp = rand() % 100; //escolhe um valor aleatório entre 0 e 99
		if(tmp <= 33) { //se tmp for menor ou igual a 33
			printf("Semaforo 1 VERDE\n");
			sem_post(&s1); //abre o semaforo para s1
		} else if (tmp <= 66) {//senão se tmp for menor ou igual a 66
			printf("Semaforo 2 VERDE\n");
			sem_post(&s2);//abre o semaforo para s2
		} else { //senão tmp é maior que 66
			printf("Semaforo 1 e 2 VERMELHO\n");
			sem_post(&principal);//volta para o controlador
		}
	} while(1); //while(1) informa que o loop é infinito
}
//Cria a função do semáforo 1
void * funcao1(void * a) {
	/*converte o 'a' de ponteiro de void para ponteiro de inteiro
	e atribui ao ponteiro de inteiro chamado valor*/
	int * valor = (int*)a; 
	
	do {//loop infinito
		sem_wait(&s1);//abre o semáforo1
		/*dá um lock no mutex para trabalhar com a variável compartilhada
		dentro da região critica*/
		pthread_mutex_lock(&mutex); 
		int tmp = *valor; //cria uma variável tmp para receber esse valor
		tmp++;//incrementa o tmp
		sleep(1); //pausa por 1 segundo
		printf("Semaforo 1 VERMELHO %d:\n",tmp);
		*valor = tmp; //devolve o tmp para a memória
		pthread_mutex_unlock(&mutex);
		sem_post(&principal);//volta para o controlador
	} while(1);
}
//essa função é igual a funcao1 mas para o s2
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
//função main principal
int main() {
	pthread_t thread[3];//crio um array de threads com 3 posições
	
	int dado = 0;//cria e inicializa um inteiro dado com valor 0
	
	/*Inicializa os semáforos com 3 parâmetros cada, o primeiro 
	parâmetro é o endereço do semáforo (com o &) o segundo é 
	sempre 0, o terceiro é 1 para o semáforo principal e 0 para 
	os demais*/
	sem_init(&principal, 0 , 1);
	sem_init(&s1, 0 , 0);
	sem_init(&s2, 0 , 0);
	
	/*Crio as threads com 4 parâmetros, o primeiro é o endereço da
	thread, o segundo parâmetro é sempre NULL, o terceiro é a função
	que a thread vai executar e o quarto é um parâmetro que pode ser
	o endereço de memória de variável, um array, uma estrutura etc
	que na função é recebido como um ponteiro de void*/
	pthread_create(&thread[0],NULL,controlador,NULL);
	pthread_create(&thread[1],NULL,funcao1,&dado);
	pthread_create(&thread[2],NULL,funcao2,&dado);
	
	/*Adiciona as threads criadas no escalonador do sistema operacional*/
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	
	/*Destroy os semáforos*/
	sem_destroy(&principal);
	sem_destroy(&s1);
	sem_destroy(&s2);
	
	return 0; //retorno de main
}











