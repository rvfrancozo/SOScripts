#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

void * funcao(void * a) {
	printf("oi mundo na thread %d com i = %d: \n",pthread_self(),*(int*)a);
	pthread_exit(0);
}

int main() {
	pthread_t thread[SIZE]; //thread[0] thread[1] ... thread[SIZE]
	
	for(int i = 0; i < SIZE; i++) {
		pthread_create(&thread[i], NULL, funcao, &i);
		pthread_join(thread[i], NULL);
	}

	return 0;
}
