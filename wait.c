#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
	pid_t	pid;
	int	status;           /* 종료 상태를 정보를 저장할 변수  */

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {     /* 자식 프로세스 처리 */
		printf("I'm a child\n");
		sleep(2);
	}
	else  {
		/* WUNTRACED 옵션은 수행을 중단한 자식 프로세스의 
		   상태를 리턴한다. */
		/*  wait(&status); */
		waitpid( pid,  &status, WUNTRACED );
		printf("A child killed with %d status\n", status);
	}
}


