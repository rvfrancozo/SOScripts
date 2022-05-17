#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //#include <unistd.h>
#include <pthread.h>

#define SIZE 5

void * funcao( void * a ) {
	int valor = *(int*) a;
	int *pointer = (int*) a; 
	int i;
	for(i = 0; i < SIZE; i++) {
		printf(" %d ",* (pointer + i) );
	}
	pthread_exit(0);
}

void sudoku () {
	
	int sudoku[9][9];
	int linha, coluna;
	srand(time(0));
	for(linha = 0; linha < 9; linha++) 
		for(coluna = 0; coluna < 9; coluna++)
			sudoku[linha][coluna] = 1 + rand() % 9;
	
	printf("JOGO DO SUDOKU\n");
	for(linha = 0; linha < 9; linha++) {
		printf("\n");
		for(coluna = 0; coluna < 9; coluna++)
			printf(" %d ",sudoku[linha][coluna]);
	}
}

int main() {
	int i;
	int dados[SIZE];
	srand(0);
	for(i = 0; i < SIZE; i++) {
		dados[i] = rand() % SIZE*2;
		printf(" %d ", dados[i]);
	}
	printf("\n");
 	
	pthread_t thread;
	pthread_create(&thread, NULL, funcao, &dados);
	
	pthread_join(thread, NULL);
	
	sudoku ();
	
	return 0;
}
