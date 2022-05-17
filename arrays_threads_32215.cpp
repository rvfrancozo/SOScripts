#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10
void * funcao (void * a) {
	int i;
	int * pointer = (int*)a;
	for(i = 0; i < SIZE; i++) {
		printf(" %d ", *(pointer + i) );
	}
	pthread_exit(0);
}
void sudoku() {
	int sudoku[9][9];
	int linha, coluna;
	srand(time(0));
	
	for(linha = 0; linha < 9; linha++) 
		for(coluna = 0; coluna < 9; coluna++)
			sudoku[linha][coluna] = 1 + rand() % 9;
			
	for(linha = 0; linha < 9; linha++) {
		printf("\n");
		for(coluna = 0; coluna < 9; coluna++)
			printf(" %d ",sudoku[linha][coluna]);
	}
		printf("\n");
}

int main() {
	sudoku();
	pthread_t thread;
	int dados [SIZE];
	int i;
	srand(time(0));
	for(i = 0; i < SIZE; i++) {
		dados[i] = rand()%SIZE*2;
		printf(" %d ", dados[i]);
	}
	printf("\n");
		
	pthread_create(&thread, NULL, funcao, &dados);
	pthread_join(thread,NULL);
	return 0;
}
