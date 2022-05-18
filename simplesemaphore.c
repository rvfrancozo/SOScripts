#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
sem_t semaforo;
  
void* thread(void* arg)
{
    //wait
    //sem_wait(&semaforo);
    printf("\Abriu...");
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nFechou...");
    //sem_post(&semaforo);
}
  
  
int main()
{
    sem_init(&semaforo, 0, 1);
    pthread_t t1,t2;
   
    pthread_create(&t1,NULL,thread,NULL);
    pthread_create(&t2,NULL,thread,NULL);
   
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
   
    sem_destroy(&semaforo);
    return 0;
}
