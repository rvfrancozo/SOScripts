#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>

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
}

void mensagem1()
{
    printf("\nSua solicitação está sendo processada... ");
}

void mensagem2()
{
    bs();
    printf("\nsolicitação concluída...");
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
    
    printf("\n");
    mensagem1();
    mensagem2();

    
    printf("\n");

    return 0;
}
