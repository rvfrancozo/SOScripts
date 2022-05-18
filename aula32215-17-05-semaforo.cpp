#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t principal, s1, s2;

void * controlador(void * a) {
	do {
		printf("Controlador ...\n");
		sem_wait(&principal);
		sleep(1);
		int tmp = rand() % 100;
		if(tmp <= 33) {
			printf("Semaforo 1 VERDE\n");
			sem_post(&s1);
		} else if (tmp <= 66) {
			printf("Semaforo 2 VERDE\n");
			sem_post(&s2);
		} else {
			printf("Semaforo 1 e 2 VERMELHO\n");
			sem_post(&principal);
		}
	} while(1);
}

void * funcao1(void * a) {
	do {
		sem_wait(&s1);
		sleep(1);
		printf("Semaforo 1 VERMELHO:\n");
		sem_post(&principal);
	} while(1);
}

void * funcao2(void * a) {
	do {
		sem_wait(&s2);
		sleep(1);
		printf("Semaforo 1 VERMELHO: \n");
		sem_post(&principal);
	} while(1);
}

int main() {
	pthread_t thread[3];
	
	int dado = 0;
	
	sem_init(&principal, 0 , 1);
	sem_init(&s1, 0 , 0);
	sem_init(&s2, 0 , 0);
	
	pthread_create(&thread[0],NULL,controlador,&dado);
	pthread_create(&thread[1],NULL,funcao1,&dado);
	pthread_create(&thread[2],NULL,funcao2,&dado);
	
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	
	sem_destroy(&principal);
	sem_destroy(&s1);
	sem_destroy(&s2);
	return 0;
}











