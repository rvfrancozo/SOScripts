#include <stdio.h> //printf scanf ...
#include <stdbool.h> //para true e false
#include <stdlib.h> //rand e srand ...
#include <pthread.h> // pthread_t, pthread_join ...
#include <time.h> //time
#include <unistd.h> //usleep e sleep

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int quadrado (int x) {
	return x*x;
}

void * funcao1(void * a) {
	int *ponteiro = (int*)a;
	do {
		pthread_mutex_lock(&mutex);//abre o mutex
		long int x = *ponteiro;
		printf("Thread id %d com valor %e\n",pthread_self(), x);
		sleep(1);
		*ponteiro = quadrado(x);
		pthread_mutex_unlock(&mutex);
	} while(1);
	pthread_exit(0);
}
void * funcao2(void * a) {
	int * ponteiro = (int*)a;
	do{
		pthread_mutex_lock(&mutex);
		long int x = *ponteiro;
		printf("Thread id %d com valor %e\n",pthread_self(), x);
		sleep(1);
		*ponteiro = quadrado(x);
		pthread_mutex_unlock(&mutex);
	}while(1);
	pthread_exit(0);
}
int main() {
	pthread_t thread[2];
	long int x = 2;
	pthread_create(&thread[0], NULL, funcao1, &x);
	pthread_create(&thread[1], NULL, funcao2, &x);
	
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	return 0;
}
