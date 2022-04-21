#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //#include <windows.h> no windows

#define SIZE 50
pthread_t thread1;
pthread_t thread2;

void *funcao1(void *a)
{
    int *valor = (int *)a;
    srand(1);

    for (int i = 0; i < SIZE; ++i)
    {
        //int tmp = *valor;
        //tmp++;
        printf("Thread 1 id : %d, valor \n", pthread_self()) ;
        

        //::Sleep( rand() % 1500 ); usar no windows
        usleep(rand() % (500 * 1000));
        //*valor = tmp;
    }

    pthread_exit(0);
}

void *funcao2(void *a)
{
    int *valor = (int *)a;
    srand(1);

    for (int i = 0; i < SIZE; ++i)
    {
        //int tmp = *valor;
        //tmp++;
        printf("Thread 2 id : %d, valor \n", pthread_self());

        //::Sleep( rand() % 1500 ); windows
        usleep(rand() % (500 * 1000));
        //*valor = tmp;
    }

    pthread_exit(0);
}

int main()
{
    int valor = 0;

    pthread_create(&thread1, NULL, funcao1, &valor);
    pthread_create(&thread2, NULL, funcao2, &valor);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("valor final %d\n\n", valor);

    return 0;
}