#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h> //unistd.h
#include <time.h>

pthread_t thread[10];

void * funcao1(void * a) {
	srand(time(0));
	do {
		Sleep( rand() % 500 );
		printf("\nOi eu sou a thread %d",pthread_self());
	} while(1);
	
	pthread_exit(0);
}
void * funcao2(void * a) {
	int x = * ((int*) a);
	srand(time(0));
	//do {
		Sleep( rand() % (x*500 ));
		printf("\nOi eu sou outra thread %d - %d",pthread_self(),x);
	//} while(1);
	
	pthread_exit(0);
}
int main () {
	int i;
	for(;;) {
		++i;
		pthread_create(&thread[i], NULL, funcao2, &i);
		pthread_join(thread[i], NULL);
	}
	/*
	pthread_create(&thread[0], NULL, funcao1, NULL);
	pthread_create(&thread[1], NULL, funcao2, NULL);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	*/
	return 0;
}
