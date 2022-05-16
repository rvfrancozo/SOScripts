#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 50

int dados[SIZE];

void init() {
	for(int i = 0; i < SIZE; i++)
		dados[i] = 0; 
}
int conta_pares() {
	int contador = 0;
	for(int i = 0; i < SIZE; i++) 
		if(dados[i] % 2 == 0) 
			contador++;
	
	printf("O vetor tem %d pares e %d impares\n",contador, SIZE-contador );	
return contador;
}

void *funcao_par(void *a) {
	srand(time(NULL));
	do {
		dados[ rand()%SIZE ] = (rand()%SIZE)/2;
		Sleep(rand()%500);
	} while(conta_pares() != SIZE/2);
	
}

void *funcao_impar(void *a) {
	do {
		dados[ rand()%SIZE ] = 1+((rand()%100)/2);
		Sleep(rand()%300);
	} while(conta_pares() != SIZE/2);
}


int main() {
	
	init();
	
	pthread_t thread1, thread2;
	
	pthread_create(&thread1, NULL, funcao_par, NULL);
	pthread_create(&thread2, NULL, funcao_impar, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	for(int i = 0; i < SIZE; i++) printf("%d ",dados[i]); 
	
	return 0;
}
