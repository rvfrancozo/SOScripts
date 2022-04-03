#include <stdio.h>       
#include <pthread.h>

void *funcao(void *argumentos) {
    printf("oi mundo\n");
    return(NULL);
}
 
int main () {
    pthread_t threads[5];

    for(int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, funcao, NULL);
    }
       


    return 0;   /* O programa chegará aqui. */ 
}