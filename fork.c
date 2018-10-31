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

		if ( ( pid = fork() ) < 0 ) {     /* 프로세스 생성 */
			perror( "fork" );
			exit(1);
		}
		
		if ( pid == 0  )  {          /* 자식 프로세스일 경우의 처리 */

	            childID = getpid();      /* 현재 프로세스의 ID를 얻어온다.*/

		    /* 0부터 프로세스 ID 까지의 합을 구한다. */
		    for ( j = 0; j <= childID ; ++j ) { 
			  sum += j;
	            }	
	            printf( "child process(%d) sum : %lf\n", childID, sum );

		    /*  void exit( int status ) 
	                프로세스를 종료할 때 사용하는 함수 
		        exit 시스템 콜은 프로세스의 종료 상태 정보 status 인자로 
		        호출된다. 종료 상태 정보는 wait() 나 waitpid() 시스템 콜에서
                        자식 프로세스가 종료되기를 기다리는 부모 프로세스에게 전달된다.
                    */
                    exit(0);	
                }	
		sum = 0.0;
	} 


	for( i = 0; i < MAX; ++i )  { 
		/*  wait 시스템 콜을 호출하여 
		    자식프로세스가 종료되거나 정지되기를 기다린다. */
		if ( ( pid = wait ( &status )  )  < 0 )  { 
			perror("wait");
			exit(1);
		}
	}


}




