#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaforo;

void * funcao( void * a ) {
	
	int * ponteiro = (int*)a;
	int valor = * (int*)a;
	
	sem_wait(&semaforo);
	printf("Abriu...%d - %d\n",pthread_self(),++valor);
	sleep(4);
	printf("Fechou...%d - %d\n",pthread_self(),++valor);
	sem_post(&semaforo);
	pthread_exit(0);
}
int main() {
	
	pthread_t thread[2];
	sem_init(&semaforo, 0, 1);
	
	int dado = 0;
	
	pthread_create(&thread[0],NULL, funcao, &dado);
	pthread_create(&thread[1],NULL, funcao, &dado);
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	sem_destroy(&semaforo);
	return 0;
}
