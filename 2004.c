3. conv.c
#include <stdio.h>

main()
{
    int     num, j, i=0;
    char    b_num[128];

    memset(b_num, 0, 128);

    printf("Input decimal number : ");
    scanf("%d", &num);
    getchar();

    while ( num != 0 )  {
        b_num[i++] = num%2;
        num /= 2;
    }

    for (j=i-1; j>=0; j--)
    {
        printf("%d", b_num[j]);
    }
    printf("\n");
}

4.mult.c
#include <stdio.h>

main(int argc, char * argv[])
{
    int     n1, n2;

    if (argc != 3)  {
        printf("Usage : %s num1 num2\n", argv[0]);
        exit(1);
    }

    n1 = atoi(argv[1]);
    n2 = atoi(argv[2]);

    printf("%d\n", n1*n2);
}


5. A:65 ~ Z:90,  a:97 ~ z:122
 Test file alphabet : count.c
#include <stdio.h>

main(int argc, char * argv[])
{
    int count =0;
    FILE * fp;
    char c;

    if (argc != 2)  {
        printf("Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "rt")) == NULL)    {
        perror("fopen");
        exit(1);
    }

    while ( (c=fgetc(fp)) != EOF )  {
        if ( c >= 'a' && c <= 'z' ) {
            count++;
        }
    }

    printf("%d\n", count);

    close(fp);
}


6. File size : size.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char * argv[])
{
    struct stat statbuf;

    if (argc != 2)  {
        printf("Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (lstat(argv[1], &statbuf)!=0)
    {
        perror("lstat");
        exit(1);
    }

    printf("%d\n", statbuf.st_size);
}

7. File mode GROUP OTHER write execute : mod.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char * argv[])
{
    struct stat statbuf;

    if (argc != 2)  {
        printf("Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (lstat(argv[1], &statbuf)!=0)
    {
        perror("lstat");
        exit(1);
    }

    if (chmod(argv[1], (statbuf.st_mode & ~S_IWGRP & ~S_IWOTH) | S_IXGRP | S_IXOTH) < 0)
    {
        perror("chmod");
        exit(1);
    }
}


8. fork()
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

main()
{
    pid_t   pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        /* chile process */
        if (execlp("./size", "size", "size.c", NULL))   {
            perror("execlp");
            exit(1);
        }
    }
    else    {
        waitpid(pid, NULL, NULL);
    }
}

9. 5 thread : threa.c
#include <stdio.h>
#include <pthread.h>

void ThreadFunc(char * msg)
{
    int i, sum=0;
    pthread_t tid = pthread_self();

    for (i=0; i<tid; i++)
        sum+=i;

    printf("%d\n", sum);
}

main()
{
    pthread_t   tid1, tid2, tid3, tid4, tid5;

    if (pthread_create(&tid1, NULL, (void *)ThreadFunc, NULL) < 0 )  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, (void *)ThreadFunc, NULL) < 0 )  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid3, NULL, (void *)ThreadFunc, NULL) < 0 )  {
        perror("pthread_create");
        exit(1);
    
    if (pthread_create(&tid4, NULL, (void *)ThreadFunc, NULL) < 0 )  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid5, NULL, (void *)ThreadFunc, NULL) < 0 )  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_join(tid1, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(tid2, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(tid3, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(tid4, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(tid5, NULL) < 0)  {
	perror("pthread_join");
        exit(1);
    }
}

10. Makefile
CCC = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
    $(CC) -c $(CFLAGS) $?

ALL = conv mult count size mod fork thread

all: $(ALL)

conv: conv.o
    $(CC) -o $@ $? $(LDFLAGS)

mult: mult.o
    $(CC) -o $@ $? $(LDFLAGS)

count: count.o
    $(CC) -o $@ $? $(LDFLAGS)

size: size.o
    $(CC) -o $@ $? $(LDFLAGS)

mod: mod.o
    $(CC) -o $@ $? $(LDFLAGS)

fork: fork.o
    $(CC) -o $@ $? $(LDFLAGS)

thread: thread.o
    $(CC) -o $@ $? $(LDFLAGS)

clean :
    rm -rf *.o $(ALL)

