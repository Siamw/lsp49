#include <stdio.h>
#include <pthread.h>

#define	  MAX	10 


void GetSum( void ) { 

	int threadID = pthread_self();             /* ���� �������� ID�� ���´�. */
	
	int i;
	double sum = 0.0;

        for ( i = 0;  i<= threadID; ++i )  {       /* ������ ID�� ���� ���Ѵ�  */ 
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
		pthread_join(  tid[i], NULL );      /* �ش� ID�� �����尡 �����ϱ⸦ ��ٸ���.*/
        } 

}
