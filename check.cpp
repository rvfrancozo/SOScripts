#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int verifica(int x, int a[9]) {
	for(int i = 0; i < 9; i++) {
		if(a[i] == x) {
			return 1; //true
		}
	}
	return 0; //false
}

void imprime(int a[9]) {
	for(int i = 0; i < 9; i++)
		printf(" %d ", a[i]);
}

int main() {
	int contador = 0;
	srand(time(0));
	int valor;
	int sudoku[9];
	
	for(int i = 0; i < 9; i++)
		sudoku[i] = 0;
		
	for(int i = 0; i < 9; i++) {
		do {
			++contador;
			valor = 1 + rand()%9;
		} while ( verifica(valor,sudoku) );
		
		sudoku[i] = valor;
	}
	
	imprime(sudoku);
	
	printf("\n Foram realizadas %d tentativas",contador); 
	
	return 0;
}
