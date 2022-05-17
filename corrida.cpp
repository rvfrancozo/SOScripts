#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h> //#include <windows.h> no windows
#include <locale.h>

pthread_t thread1;
pthread_t thread2;
int ano = 2000;

void *mostra(void *a)
{
    int *valor = (int *)a;
    //usleep(500*1000); //
	//Sleep(500); //no windows para dormir 0,5 segundos
    ano = 1985;
    printf("Thread 1 id: %d, O ano de nascimento é: %d\n\n", pthread_self(), ano);

    pthread_exit(0);
}

void *calcula(void *a)
{
    int *valor = (int *)a;

    printf("Thread 2 id: %d, A idade é: %d\n\n", pthread_self(),  2022 - ano);

    pthread_exit(0);
}

int main()
{
	
	setlocale(LC_ALL, "Portuguese");

    pthread_create(&thread1, NULL, mostra, NULL);
    pthread_create(&thread2, NULL, calcula, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
