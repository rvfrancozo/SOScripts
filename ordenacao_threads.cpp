#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 30000

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
	int count = 0;
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = SIZE - 1; j >= i; j--)
        {
            if (dados[j - 1] > dados[j])
            {
                tmp = dados[j - 1];
                dados[j - 1] = dados[j];
                dados[j] = tmp;
            }
            ++count;
        }
    }
    printf("Bubble Sort Finalizado com %d passos\n",count);
}

void *thread_ss(void *a)
{
	int count = 0;
    int j;
    for (int k = 0; k < SIZE; k++)
    {
        int gap = k;
        for (int i = gap; i < SIZE; i++)
        {
            tmp = dados2[i];
            for (j = i - gap; tmp < dados2[j] && j >= 0; j = j - gap) {
            	dados2[j + gap] = dados2[j];
            	++count;
			}
            dados2[j + gap] = tmp;
        }
    }
    printf("Shell Sort Finalizado com %d passos\n",count);
}

int main()
{
    init();

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_bs, NULL);
    pthread_create(&thread2, NULL, thread_ss, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
