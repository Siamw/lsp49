#include <stdio.h>
#include <stdlib.h>

int mysystem( char *cmd )
{
	int pid;
	int status;

		
	if (  ( pid = fork() ) < 0 ) {	    /* ���μ��� ���� */ 
		perror( "fork " );
		exit(1);
	}
	else if ( pid == 0 ) {		    /* �ڽ� ���μ��� ó�� */	
		if (  execlp( cmd , cmd  , "-al", NULL ) < 0 ) {
			perror ("execlp");
			exit(1);
		}
	}
	else
	{
		waitpid( pid, &status ,NULL );    /* �ڽ�  ���μ��� ����� ���� ��� */
	}

}

main()
{
	mysystem( "ls" );				
}
