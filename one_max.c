#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION 100
#define SIZE 100

int pop[POPULATION][SIZE];

void init()
{
    srand(time(0));
    for (int i = 0; i < POPULATION; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((float)rand() / RAND_MAX > 0.5)
                pop[i][j] = 1;
            else
                pop[i][j] = 0;
        }
    }
}
void print_pop()
{
    for (int i = 0; i < POPULATION; i++)
    {
        printf("\n");
        for (int j = 0; j < SIZE; j++)
            printf("%d", pop[i][j]);
    }
}
void print_individuo(int individuo)
{
    for (int j = 0; j < SIZE; j++)
        printf("%d", pop[individuo][j]);
}
int score(int individuo[SIZE])
{
    int score = 0;
    for (int j = 0; j < SIZE; j++)
        score += individuo[j];
    return score;
}
int best_score()
{
    int score = 0;
    int best = 0;
    for (int i = 0; i < POPULATION; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            score += pop[i][j];
        }
        if (score > best)
            best = score;
            score = 0;
    }
    return best;
}

int crossover()
{
    srand(time(0));
    int a1 = rand() % POPULATION;
    int a2 = rand() % POPULATION;
    int new[SIZE];
    for (int i = 0; i < SIZE / 2; i++)
        new[i] = pop[a1][i];
    for (int i = SIZE / 2; i < SIZE; i++)
        new[i] = pop[a2][i];

    // Mutate
    while (score(new) < best_score())
    {
        new[rand() % SIZE] = 1;
    }

    int a = rand() % POPULATION;
    if (score(new) > best_score())
    {
        for (int i = 0; i < SIZE; i++)
            pop[a][i] = new[i];
        for (int j = 0; j < SIZE; j++)
            printf("%d", new[j]);
        printf(" Score atual: %d\n", score(new));
    }

    return score(new);
}

int main()
{
    int score = 0;
    init();
    printf("%d \n", best_score());
    do
    {
        score = crossover();
    } while (score < 80);

    // print_pop();

    printf("%d", rand() % POPULATION);

    return 0;
}