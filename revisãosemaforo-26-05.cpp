#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t principal, s1, s2, s3, s4;

void * controlador(void * a) {
	srand(time(0));
	do {
		sleep(1);
		int tmp = rand() % 5;
		sem_wait(&principal);
		if(tmp == 0) { 
			printf("Vez da funcao 1\n");
			sem_post(&s1);
		} else if(tmp == 1) {
			printf("Vez da funcao 2\n");
			sem_post(&s2);
		} else if(tmp == 2) { 
			printf("Vez da funcao 3\n");
			sem_post(&s3);
		} else if(tmp == 3) {
			printf("Vez da funcao 4\n");
			sem_post(&s4);			
		} else {
			printf("Permanece no controlador\n");
			sem_post(&principal);			
		}
	} while(1);
	pthread_exit(0);
}
void * funcao1(void * a) {
	do{
		sem_wait(&s1);
		printf("Funcao 1 executando...");
		sem_post(&principal);
	} while(1);
}
void * funcao2(void * a) {
	do{
		sem_wait(&s2);
		printf("Funcao 2 executando...");
		sem_post(&principal);
	} while(1);
}
void * funcao3(void * a) {
	do{
		sem_wait(&s3);
		printf("Funcao 3 executando...");
		sem_post(&principal);
	} while(1);
}
void * funcao4(void * a) {
	do{
		sem_wait(&s4);
		printf("Funcao 1 executando...");
		sem_post(&principal);
	} while(1);
}

int main() {
	pthread_t thread[5];
	sem_init(&principal, 0, 1);
	sem_init(&s1, 0, 0);
	sem_init(&s2, 0, 0);
	sem_init(&s3, 0, 0);
	sem_init(&s4, 0, 0);	
	pthread_create(&thread[0], NULL, controlador, NULL);
	pthread_create(&thread[1], NULL, funcao1, NULL);
	pthread_create(&thread[2], NULL, funcao2, NULL);
	pthread_create(&thread[3], NULL, funcao3, NULL);
	pthread_create(&thread[4], NULL, funcao4, NULL);	
	for(int i = 0; i < 5; i++) 
		pthread_join(thread[i],NULL);		
	sem_destroy(&principal);
	sem_destroy(&s1);
	sem_destroy(&s2);
	sem_destroy(&s3);
	sem_destroy(&s4);	
	return 0;
}
















