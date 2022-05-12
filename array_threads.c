#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 5

void *funcao(void *a)
{
    for (int i = 0; i < SIZE; i++)
    {
        int *valor = (int *)a;
        printf(" %d ", *(valor + i));
    }
}

int main()
{
    srand(time(0));
    int dados[SIZE];
    int sudoku[9][9];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sudoku[i][j] = 1 + rand() % 9;

    printf("JOGO DO SUDOKU");
    for (int i = 0; i < 9; i++)
    {
        printf("\n");
        for (int j = 0; j < 9; j++)
            printf(" %d ", sudoku[i][j]);
    }

    for (int i = 0; i < SIZE; i++)
    {
        dados[i] = rand() % 10;
        printf("\n%d", dados[i]);
    }

    pthread_t thread;

    pthread_create(&thread, NULL, funcao, &dados);

    pthread_join(thread, NULL);

    return 0;
}