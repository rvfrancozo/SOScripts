#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo;

void * funcao(void * a) {
	sem_wait(&semaforo); //Sinal Vermelho 
	printf("Abriu...%d\n",pthread_self());
	sleep(4);
	printf("Fechou...%d\n",pthread_self());
	sem_post(&semaforo); //Sinal Verde
}
int main() {
	
	sem_init(&semaforo, 0, 1);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, funcao, NULL);
	sleep(1);
	pthread_create(&t2, NULL, funcao, NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	sem_destroy(&semaforo);
	
	return 0;
}
