#include <stdio.h>
#include <limits.h>
#include <string.h>

#define VERTEX 10

int graph[VERTEX][VERTEX];

void initGraph() {
    int i,j;
    for(i = 0; i < VERTEX; i++) 
        for(j = 0; j < VERTEX; j++) 
            graph[i][j] = INT_MAX;

    graph[0][1] = 3;
    graph[0][2] = 5;
    graph[0][4] = 9;
    graph[1][2] = 1;
    graph[1][5] = 4;
    graph[2][5] = 4;
    graph[3][6] = 8;
    graph[4][5] = 1;
    graph[4][8] = 9;
    graph[5][6] = 1;
    graph[5][7] = 12;
    graph[5][9] = 40;
    graph[6][9] = 14;
    graph[7][8] = 13;
    graph[8][9] = 2;
}

void  dijkstra(int origem, int destino) {
    int custoTotal = 0;
    int custo,v;
    printf("O melhor caminho de %d para %d é:\n %d",origem,destino,origem);

    do {
        printf("-");
        custo = INT_MAX;
        for(int i = origem+1; i < VERTEX; i++) {
            if(graph[origem][i] < custo) {
                custo = graph[origem][i];
                v = i;
            }
        }
        origem = v;
        custoTotal += custo;
        printf("%d", origem);
    } while(origem < destino);

    printf("\nCom custo de %d:\n\n",custoTotal);

}

int main() {

    initGraph();
    dijkstra(0,9);

    return 0;
}