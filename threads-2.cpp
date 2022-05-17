#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void *funcao1(void *a) {
	srand(time(NULL));
	do {
		a = (int*) (rand()%100);
		printf("Thread 1 atualizou para %d:\n", a);
		Sleep(500);
	} while(true);
	
}

void *funcao2(void *a) {
	do {
		a = (int*) (rand()%100);
		printf("Thread 02 atualizou para %d:\n", a);
		Sleep(100);
	} while(true);
}
int main() {
	
	int valor;
	
	pthread_t thread1, thread2;
	
	pthread_create(&thread1, NULL, funcao1, (void*)valor);
	pthread_create(&thread2, NULL, funcao2, (void*)valor);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	return 0;
}
