#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <process.h>

pthread_mutex_t lock;
pthread_t rotina[ 2 ];

void * rotina_f1( void * p_param )
{
    int * valor = (int *)p_param;
    srand( 1 );

    for( int i = 0; i < 10; ++i )
    {
        pthread_mutex_lock( &lock );
        int tmp = *valor;
        tmp++;
        printf( "f1 id : %d, valor %d\n\n", pthread_self(), *valor );

        ::Sleep( rand() % 1500 );
        *valor = tmp;
        pthread_mutex_unlock( &lock );
    }

    pthread_exit( 0 );
}

void * rotina_f2( void * p_param )
{
    int * valor = (int *)p_param;
    srand( 1 );

    for( int i = 0; i < 10; ++i )
    {
        pthread_mutex_lock( &lock );
        int tmp = *valor;
        tmp++;
        printf( "f2 id : %d, valor %d\n\n", pthread_self(), *valor );

        ::Sleep( rand() % 1500 );
        *valor = tmp;
        pthread_mutex_unlock( &lock );
    }

    pthread_exit( 0 );
}

int main()
{
    printf( "INICIANDO...\n\n");
    int valor = 0;

    pthread_create( &rotina[ 0 ], NULL, rotina_f1, &valor );
    pthread_create( &rotina[ 1 ], NULL, rotina_f2, &valor );

    pthread_join( rotina[ 0 ], NULL );
    pthread_join( rotina[ 1 ], NULL );

    printf( "valor final %d\n\n", valor );
    printf( "ENCERRADO.\n\n");
    return 0;
}
