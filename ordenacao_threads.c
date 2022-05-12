#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int dados[SIZE];
int dados2[SIZE];
int tmp;

void init()
{
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {
        dados[i] = rand() % SIZE * 2;
        dados2[i] = dados[i];
    }
}

void *thread_bs(void *a)
{
    for (int i = 1; i < SIZE; i++)
    {
        printf("Thread %d ID: %d executando... BS\n",a,pthread_self());
        for (int j = SIZE - 1; j >= i; j--)
        {
            if (dados[j - 1] > dados[j])
            {
                tmp = dados[j - 1];
                dados[j - 1] = dados[j];
                dados[j] = tmp;
            }
        }
    }
}

void *thread_ss(void *a)
{
    int j;
    for (int k = 0; k < SIZE; k++)
    {
        printf("Thread %d ID: %d executando... SS\n",a,pthread_self());
        int gap = k;
        for (int i = gap; i < SIZE; i++)
        {
            tmp = dados2[i];
            for (j = i - gap; tmp < dados2[j] && j >= 0; j = j - gap)
                dados2[j + gap] = dados2[j];
            dados2[j + gap] = tmp;
        }
    }
}

int main()
{
    init();

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_bs, (void *)(1));
    pthread_create(&thread2, NULL, thread_ss, (void *)(2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    puts("\nOrdenado com Bubble Sort: ");
    for(int i = 0; i < SIZE; i++)
        printf(" %d ",dados[i]);

    puts("\nOrdenado com Shell Sort: ");
    for(int i = 0; i < SIZE; i++)
        printf(" %d ",dados2[i]);

    return 0;
}