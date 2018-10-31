#include <stdio.h>
#include <pthread.h>

#define	  MAX	10 


void GetSum( void ) { 

	int threadID = pthread_self();             /* 현재 쓰레드의 ID를 얻어온다. */
	
	int i;
	double sum = 0.0;

        for ( i = 0;  i<= threadID; ++i )  {       /* 스레드 ID의 합을 구한다  */ 
		sum += i;
	}
	
	printf("Thread ID ( %d ) sum : %lf\n", threadID, sum );

}



main() {
	
	pthread_t tid[MAX];
	int i;
	
	for( i = 0; i < MAX; i++ )  { 
	
	if( pthread_create( &tid[i], NULL, (void*)GetSum, NULL ) < 0 )
	{
		perror("pthread_create");
		exit(1);
	}

        } 

        for( i = 0; i < MAX; ++i )  { 
		pthread_join(  tid[i], NULL );      /* 해당 ID의 쓰레드가 종료하기를 기다린다.*/
        } 

}
