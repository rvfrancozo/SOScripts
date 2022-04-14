#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

void bs()
{
    int tmp;
    int dados[SIZE];
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {

        dados[i] = rand() % SIZE;
    }

    printf("Sua solicitação está sendo processada... ");

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
        }
    }
    printf("\nsolicitação concluída...");
}

void *mensagem1(void *a)
{
    printf("\nSua solicitação está sendo processada... ");
    pthread_exit(0);
}

void *mensagem2(void *a)
{
    printf("\nsolicitação concluída...");
    bs();
    pthread_exit(0);
}

int main()
{

    // bs();
    printf("\n");
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, mensagem1, (void *)(1));
    pthread_create(&thread2, NULL, mensagem2, (void *)(2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    
    printf("\n");

    return 0;
}