#include <stdio.h>

#define MAX 100

main(int argc, char * argv[])
{
    FILE    *fp;
    char    line[MAX];
    int     cntline=0;

    if (argc != 3)  {
        printf("Usage : %s string filename\n", argv[0]);
        exit(1);
    }

    /* 파일을 text, read모드로 연다 */
    if ( (fp = fopen(argv[2], "rt") ) == NULL) {
        perror("fopen");
        exit(1);
    }

    /* 파일에서 한라인의 문자열을 읽어들인다. */
    while (fgets(line, MAX, fp) != NULL)   {
	/* 읽어들인 문자열 중에 인수로 전달된 문자열이 있으면 출력한다.*/
        if (strstr(line, argv[1]))  {
                printf("%s", line);
        }
    }

    close(fp);
}

