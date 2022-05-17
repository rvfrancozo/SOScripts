#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <process.h>

pthread_t thread1, thread2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * funcao1 (void * a) {
	int * x = (int *)a;
	//int x = * (int*) a //pega o valor;
	srand(1);
	
	for(int i = 0; i < 10; ++i) {
		pthread_mutex_lock(&mutex);
		int tmp = *x;
		tmp++;
		printf("F1 id: %d, valor %d\n",pthread_self(), *x);
		
		Sleep(rand() % 1500);
		*x = tmp;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

void * funcao2 (void * a) {
	int * x = (int *)a;
	srand(1);
	
	for(int i =0; i < 10; ++i) {
		pthread_mutex_lock(&mutex);
		int tmp = *x;
		tmp++;
		printf("F2 id: %d, valor %d\n",pthread_self(), *x);
		
		Sleep(rand() % 1500);
		*x = tmp;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

int main() {
	int dado = 0;
	
	pthread_create(&thread1, NULL, funcao1, &dado);
	pthread_create(&thread2, NULL, funcao2, &dado);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	return 0;
}
