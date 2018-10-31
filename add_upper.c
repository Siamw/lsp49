6. command line 두숫자의 합 : add.c
$ ./add 10 12

#include <stdio.h>

main(int argc, char * argv[])
{
    int     num1, num2;

    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);

    printf("%d\n", num1+num2);
}


7. : toupper.c
$ ./toupper toupper.c toupper.c.upper

#include <stdio.h>

main(int argc, char *argv[])
{
    FILE *src, *dst;
    int  ch;

    if (argc !=3) {
        fprintf(stderr, "Usage : %s source destination\n", argv[0]);
        exit(1);
    }

    if ((src = fopen(argv[1], "rt")) == NULL) {
        perror("fopen");
        exit(1);
    }

    if ((dst = fopen(argv[2], "wt")) == NULL) {
        perror("fopen");
        exit(1);
    }

    while ((ch = fgetc(src)) != EOF) {
        if (ch >= 'a' && ch <= 'z')
            ch = ch - 32;

        fputc(ch, dst);
    }
}

8. permission: file.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

main(int argc, char *argv[])
{
    struct stat statbuf;

     if (mkdir("temp", 0755) != 0)  {
        perror("rmdir");
        exit(1);
    }

    if (creat("./temp/my.file", 0644) < 0)  {
        perror("create");
        exit(1);
    }

    if (lstat("./temp/my.file", &statbuf) < 0)  {
        perror("lstat");
        exit(1);
    }

    printf("user id = %d\n", statbuf.st_uid);
    printf("group id = %d\n", statbuf.st_gid);

    if (symlink("./temp/my.file", "/export/home/usp/usp03/my.ln") < 0) {
        perror("symlink");
        exit(1);
    }

    if (rename("./temp/my.file", "./temp/my.file.new") < 0) {
        perror("rename");
        exit(1);
    }
}

9. 10개의 child process. child종료후 종료하는 프로그램 fork를 작성
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
    pid_t   pid;
    int     i, j;
    int     sum =0;

    for (i=0; i<10; i++)    {
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }
        else if ( pid == 0 )    {
            for (j=0; j<getpid(); j++)  {
                sum += j;
            }

            printf("Process ID : %d, Sum = %d\n", getpid(), sum);
            exit(1);
        }
        else {
            waitpid(pid, NULL, NULL);
        }
    }
}

