#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <process.h>

#define SIZE 10

pthread_t rotina[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * funcao1( void * parametro) {

	int * x = (int*) parametro;
	srand(1);
	for(int i = 0; i < SIZE; i++) {
		pthread_mutex_lock(&mutex);
		int tmp = * x;
		tmp++;
		printf("\nThread ID: %d com valor: %d",pthread_self(),tmp);
		Sleep(rand()%500);
		*x = tmp;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}
void * funcao2( void * parametro) {

	int * x = (int*) parametro;
	srand(1);
	for(int i = 0; i < SIZE; i++) {
		pthread_mutex_lock(&mutex);
		int tmp = * x;
		tmp++;
		printf("\nThread ID: %d com valor: %d",pthread_self(),tmp);
		Sleep(rand()%1500);
		*x = tmp;
		//pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

int main() {
	
	int x = 0;
	
	pthread_create(&rotina[0], NULL, funcao1, &x);
	pthread_create(&rotina[1], NULL, funcao2, &x);
	
	pthread_join(rotina[0], NULL);
	pthread_join(rotina[1], NULL);
	
	return 0;
}
