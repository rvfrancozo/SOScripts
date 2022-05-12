#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void *thread_bs(void *a)
{
    int i, tmp;
    for (int i = 1; i < SIZE; i++)
    {
        // printf("Thread %d ID: %d executando... BS\n", a, pthread_self());
        for (int j = SIZE - 1; j >= i; j--)
        {
            if (*(int *)(a + (j - 1)) > *(int *)(a + j))
            {
                tmp = *(int *)(a + (j - 1));
                *(int *)(a + (j - 1)) = *(int *)(a + j);
                *(int *)(a + j) = tmp;
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
        printf("\n%d", *(int *)(a + i));
}

// void *thread_ss(void *a)
// {
//     int j;
//     for (int k = 0; k < SIZE; k++)
//     {
//         printf("Thread %d ID: %d executando... SS\n", a, pthread_self());
//         int gap = k;
//         for (int i = gap; i < SIZE; i++)
//         {
//             tmp = dados[i];
//             for (j = i - gap; tmp < dados[j] && j >= 0; j = j - gap)
//                 dados[j + gap] = dados[j];
//             dados[j + gap] = tmp;
//         }
//     }
// }

int main()
{
    int dados[SIZE];
    int tmp;
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
        dados[i] = rand() % SIZE * 2;

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_bs, &dados);
    // pthread_create(&thread2, NULL, thread_ss, &dados);

    pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);

    return 0;
}