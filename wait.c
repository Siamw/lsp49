#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
	pid_t	pid;
	int	status;           /* ���� ���¸� ������ ������ ����  */

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {     /* �ڽ� ���μ��� ó�� */
		printf("I'm a child\n");
		sleep(2);
	}
	else  {
		/* WUNTRACED �ɼ��� ������ �ߴ��� �ڽ� ���μ����� 
		   ���¸� �����Ѵ�. */
		/*  wait(&status); */
		waitpid( pid,  &status, WUNTRACED );
		printf("A child killed with %d status\n", status);
	}
}


