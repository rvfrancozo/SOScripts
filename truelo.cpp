#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>
#include <semaphore.h>

#define TIME 1000000

sem_t s_juiz, s_black, s_gray, s_white;

void * juiz(void * a) {
	do {
		sem_wait(&s_juiz);
		sleep(1);
		printf("Juiz decide que o ");
		int tmp = rand()%100;
		if(tmp <= 33) {
			printf("Sr. Black Atira: \n");
			sem_post(&s_black);
		} else if(tmp <= 66) {
			printf("Sr. Gray Atira: \n");
			sem_post(&s_gray);
		} else {
			printf("Sr. White Atira: \n");
			sem_post(&s_white);
		}
		
	} while(1);
	pthread_exit(0);
}
void * black(void * a) {
	do {
		sem_wait(&s_black);
		sleep(1);
		if (rand()%10 <= 3)
			printf("Sr. Black Acertou\n");
		else 
			printf("Sr. Black Errou\n");
		sem_post(&s_juiz);
	} while(1);
	pthread_exit(0);
}
void * gray(void * a) {
	do {
		sem_wait(&s_gray);
		sleep(1);
		if (rand()%10 <= 6)
			printf("Sr. Gray Acertou\n");
		else 
			printf("Sr. Gray Errou\n");
		sem_post(&s_juiz);
	} while(1);
	pthread_exit(0);
}
void * white(void * a) {
	do {
		sem_wait(&s_white);
		sleep(1);
		printf("Sr. White Acertou\n");
		sem_post(&s_juiz);
	} while(1);
	pthread_exit(0);
}
int main() {
	
	pthread_t thread[4];	
	srand(time(0));
	int i = 0;
	
	sem_init(&s_juiz, 0, 1);
	sem_init(&s_black, 0, 0);
	sem_init(&s_gray, 0, 0);
	sem_init(&s_white, 0, 0);
	
	pthread_create(&thread[0], NULL, juiz, &i);
	pthread_create(&thread[1], NULL, black, &i);
	pthread_create(&thread[2], NULL, gray, &i);
	pthread_create(&thread[3], NULL, white, &i);
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);
	
	sem_destroy(&s_juiz);
	sem_destroy(&s_black);
	sem_destroy(&s_gray);
	sem_destroy(&s_white);
	
	return 0;
}






