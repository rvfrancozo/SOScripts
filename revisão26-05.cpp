#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * funcao(void * a) {
	pthread_mutex_lock(&mutex);
	int tmp = *(int*)a; 
	printf("%s %i\n", tmp % 2 == 0 ? "Valor par" : "Valor impar",tmp);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
void * funcao2(void * a) {
	pthread_mutex_lock(&mutex);
	int tmp = *(int*)a; 
	int b;
	for(int i = tmp - 1; tmp >=2; tmp--) {
		b = 1;
		if(tmp % i == 0) {
			printf("O numero %d nao eh primo\n",tmp);
			b = 0;
			break;
		}
		if(b || tmp == 2)
			printf("O numero %d eh primo\n",tmp);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

int main() {
	srand(time(0));
	pthread_t thread[SIZE];
	pthread_t th[SIZE];
	for(int i = 0; i < SIZE; i++) {
		int x = rand() % SIZE;
		pthread_create(&thread[i],NULL,funcao,&x);
		pthread_create(&th[i],NULL,funcao2,&x);
		pthread_join(thread[i], NULL);
		pthread_join(th[i], NULL);
	}
	return 0;
}
