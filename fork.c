#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX   10 


main() { 
        int i;
	int j;
	pid_t pid;
	pid_t childID;
	double sum = 0.0;
	int status;
	
	for( i = 0;  i < MAX;  ++i ) {

		if ( ( pid = fork() ) < 0 ) {     /* ���μ��� ���� */
			perror( "fork" );
			exit(1);
		}
		
		if ( pid == 0  )  {          /* �ڽ� ���μ����� ����� ó�� */

	            childID = getpid();      /* ���� ���μ����� ID�� ���´�.*/

		    /* 0���� ���μ��� ID ������ ���� ���Ѵ�. */
		    for ( j = 0; j <= childID ; ++j ) { 
			  sum += j;
	            }	
	            printf( "child process(%d) sum : %lf\n", childID, sum );

		    /*  void exit( int status ) 
	                ���μ����� ������ �� ����ϴ� �Լ� 
		        exit �ý��� ���� ���μ����� ���� ���� ���� status ���ڷ� 
		        ȣ��ȴ�. ���� ���� ������ wait() �� waitpid() �ý��� �ݿ���
                        �ڽ� ���μ����� ����Ǳ⸦ ��ٸ��� �θ� ���μ������� ���޵ȴ�.
                    */
                    exit(0);	
                }	
		sum = 0.0;
	} 


	for( i = 0; i < MAX; ++i )  { 
		/*  wait �ý��� ���� ȣ���Ͽ� 
		    �ڽ����μ����� ����ǰų� �����Ǳ⸦ ��ٸ���. */
		if ( ( pid = wait ( &status )  )  < 0 )  { 
			perror("wait");
			exit(1);
		}
	}


}




