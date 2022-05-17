#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <semaphore.h>

#define NUM_THREAD 4

sem_t semaforo;

void * rotina ( void * a ) {
	sem_wait(&semaforo);
	Sleep(1);
	printf("Hello thread %d\n",*(int*)a);
	sem_post(&semaforo);
	free(a);
	pthread_exit(0);
}

int main () {
	
	pthread_t thread[NUM_THREAD];
	sem_init(&semaforo,0,1);
	int i;
	for(i = 0; i < NUM_THREAD; i++) {
		pthread_create(&thread[i],NULL,rotina,&i);
		pthread_join(thread[i],NULL);
	}
	for(i = 0; i < NUM_THREAD; i++) {
	//	pthread_join(thread[i],NULL);
	}
	sem_destroy(&semaforo);
	return 0;
}
