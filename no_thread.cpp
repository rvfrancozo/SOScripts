#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>
#include <semaphore.h>

#define TIME 1000000

void * juiz(void * a) {
	do {
		usleep(rand()%TIME);
		printf("Em posse do Juiz\n");
	} while(1);
}
void * black(void * a) {
	do {
		usleep(rand()%TIME);
		printf("Atira o Sr. Black\n");
	} while(1);
}
void * gray(void * a) {
	do {
		usleep(rand()%TIME);
		printf("Atira o Sr. Gray\n");
	} while(1);
}
void * white(void * a) {
	do {
		usleep(rand()%TIME);
		printf("Atira o Sr. White\n");
	} while(1);
}
int main() {
	
	int i = 0;
	
	juiz(&i);
	black(&i);
	gray(&i);
	white(&i);
	
	return 0;
}






