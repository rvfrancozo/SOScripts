#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int cartela[9][9];

void init() {
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			cartela[i][j] = 0;
	cartela[0][0] = 5;
	cartela[0][1] = 3;
	cartela[0][4] = 7;
	cartela[1][0] = 6;
	cartela[1][3] = 1;
	cartela[1][4] = 9;
	cartela[1][5] = 5;
	cartela[2][1] = 9;
	cartela[2][2] = 8;
	cartela[2][1] = 9;
	
}
