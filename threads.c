/*
Exemplo de Threads em C código testado no KDE Neon com VS Code
Para compilar faça gcc -pthread threads.c -o threads.o ; ./threads.o
*/
#include <stdio.h>
#include <pthread.h>

#define THREADS 6

int v[THREADS];

void * funcao(void * a) {
    int *valor = (int*)(a);
    if(*valor == 1) {
        printf("Thread 1 executando...\n");
        for(int i = 0; i < THREADS/2; i++) {
            v[i] = 0;
        }
    } else {
        printf("Thread 2 executando...\n");
        for(int i = THREADS/2; i < THREADS;i++) {
            v[i] = 1;
        }
    }
}

int main()
{
    pthread_t thread1, thread2;
    int x = 0;
    int y = 1;

    pthread_create(&thread1, NULL, funcao, (void*)(&x));
    pthread_create(&thread2, NULL, funcao, (void*)(&y));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    for(int i = 0; i < THREADS; i++)
        printf("%d ",v[i]);
    
}