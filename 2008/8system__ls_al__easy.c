#include <stdio.h>
#include <stdlib.h>

int mysystem( char *cmd )
{
	int pid;
	int status;

		
	if (  ( pid = fork() ) < 0 ) {	    /* 프로세스 생성 */ 
		perror( "fork " );
		exit(1);
	}
	else if ( pid == 0 ) {		    /* 자식 프로세스 처리 */	
		if (  execlp( cmd , cmd  , "-al", NULL ) < 0 ) {
			perror ("execlp");
			exit(1);
		}
	}
	else
	{
		waitpid( pid, &status ,NULL );    /* 자식  프로세스 종료시 까지 대기 */
	}

}

main()
{
	mysystem( "ls" );				
}
