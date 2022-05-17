#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s0, s1, s2;
int temp = 0;

void *observador(void *a)
{
    while (1)
    {
        printf("Observador esperando...\n");
        sem_wait(&s0);
        usleep(100000);

        temp = rand() % 100;

        if (temp <= 33)
        {
            printf("Semaforo 1 VERDE\n");
            sem_post(&s1);
        }
        else if (temp <= 66)
        {
            printf("Semaforo 2 VERDE\n");
            sem_post(&s2);
        }
        else
        {
            printf("Semaforo 1 e 2 VERMELHO\n");
            sem_post(&s0);
        }
    }
    pthread_exit(0);
}

void *funcao1(void *a)
{
    int timer = 5;
    int *valor = (int *)a;
    while (1)
    {
        int tmp = *valor;
        printf("Semaforo 1 Vermelho = %d\n", ++tmp);
        sem_wait(&s1);
        usleep(500000);

        --timer;

        if (timer <= 0)
        {
            timer = 5;
        }
        *valor = tmp;
        sem_post(&s0);
        printf("Semaforo 1 VERDE\n");
    }
    pthread_exit(0);
}

void *funcao2(void *a)
{
    int timer = 5;
    int *valor = (int *)a;
    while (1)
    {
        int tmp = *valor;
        printf("Semaforo 2 Vermelho = %d\n", ++tmp);
        sem_wait(&s2);
        usleep(500000);

        --timer;

        if (timer <= 0)
        {
            timer = 5;
        }
        *valor = tmp;
        sem_post(&s0);
        printf("Semaforo 2 VERDE\n");
    }
    pthread_exit(0);
}

int main()
{

    pthread_t thread0, thread1, thread2;
    srand(time(NULL));

    int valor = 0;

    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    pthread_create(&thread0, NULL, observador, &valor);
    pthread_create(&thread1, NULL, funcao1, &valor);
    pthread_create(&thread2, NULL, funcao2, &valor);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);

    return 0;
}