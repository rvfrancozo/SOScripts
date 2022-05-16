#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <time.h>

pthread_t thread[2];

void * funcao1(void * a) {
	
	//int x = * ((int*) a);
	srand(time(NULL));
	Sleep( rand() % 250);
	printf(" Ola");
	
	pthread_exit(0);
}

void * funcao2(void * a) {
	
	//int x = * ((int*) a);
	srand(time(NULL));
	Sleep( rand() % 250);
	printf(" Thread");
	
	pthread_exit(0);
}

int main() {
	
	int parametro = 1;
	
	pthread_create(&thread[0], NULL, funcao1, &parametro);
	pthread_create(&thread[1], NULL, funcao2, &parametro);
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	return 0;
}
