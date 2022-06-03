#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int quadrado(int x) {
	return x*x;
}
void * funcao(void * a) {
	int tmp =  quadrado ( *(int*)a ); 
	printf("Thread ID: %d com valor: %i\n", pthread_self(),tmp);
	pthread_exit(0);
}
int main() {
	
	pthread_t thread[10]; //declaro a thread
	for(int i = 0; i < 10; ++i) {
		pthread_create(&thread[i],NULL,funcao,&i); //cria a thread
		pthread_join(thread[i],NULL);//adiciona no escalonador
	}
	return 0;
}
