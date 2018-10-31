#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
        pid_t pid;
        int status;

        if( ( pid = fork() ) < 0 )  {
                perror( "fork" );
                exit(1);
        }
        else if ( pid == 0 )  {   /* 자식 프로세스 처리 */
		
		
                execl("/export/home/usp/usp37/midterm/mywc",
                                 "mywc" , "mywc.c", NULL );
        }
        else
        {
                wait(&status);
        }

}
