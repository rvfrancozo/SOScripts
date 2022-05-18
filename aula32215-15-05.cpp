#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#define SIZE 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * funcao1(void * a) {
	int valor = *(int*)a; //valor recebe o valor de a
	int * pointer = (int*)a; //pointer um ponteiro que recebe o end de a
	int i;
	for(i = 0; i < SIZE; i++) {
		pthread_mutex_lock(&mutex);
		int tmp = * pointer;
		tmp++;
		printf("\nThread id: %d com valor %d",pthread_self(), tmp);
		Sleep(rand()%1500);
		* pointer = tmp;
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(0);
}

void * funcao2(void * a) {
	int valor = *(int*)a; //valor recebe o valor de a
	int * pointer = (int*)a; //pointer � um ponteiro que recebe o end de a
	int i;
	for(i = 0; i < SIZE; i++) {
		pthread_mutex_lock(&mutex);
		int tmp = * pointer;
		tmp++;
		printf("\nThread id: %d com valor %d",pthread_self(), tmp);
		Sleep(rand()%1500);
		* pointer = tmp;
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(0);
}

int main() {
	pthread_t thread[2];
	int x = 0;
	pthread_create(&thread[0], NULL, funcao1, &x);
	pthread_create(&thread[1], NULL, funcao2, &x);
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	return 0;
}
