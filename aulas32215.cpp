#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h> //unistd.h

pthread_t thread[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * funcao1 ( void * parametro) {
	int * valor = (int*)parametro;
	srand(1);
	do {
		pthread_mutex_lock(&mutex);
		int tmp = *valor;
		tmp++;
		Sleep( rand() % 500 ); //usleep(150000);
		printf(" \nThread id: %d valor: %d",pthread_self(),tmp);
		*valor = tmp;
		pthread_mutex_unlock(&mutex);
	} while(1);
	pthread_exit(0);
}
void * funcao2 ( void * parametro) {
	int * valor = (int*)parametro;
	srand(1);
	do {
		pthread_mutex_lock(&mutex);
		int tmp = *valor;
		tmp++;
		Sleep( rand() % 1500 ); //usleep();
		printf(" \nThread id: %d valor: %d",pthread_self(),tmp);
		*valor = tmp;
		pthread_mutex_unlock(&mutex);
	} while(1);
	pthread_exit(0);
}

int main() {
	
	int x = 0;
	
	pthread_create(&thread[0], NULL, funcao1, &x);
	pthread_create(&thread[1], NULL, funcao2, &x);
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	return 0;
}
