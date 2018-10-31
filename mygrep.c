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

    /* ������ text, read���� ���� */
    if ( (fp = fopen(argv[2], "rt") ) == NULL) {
        perror("fopen");
        exit(1);
    }

    /* ���Ͽ��� �Ѷ����� ���ڿ��� �о���δ�. */
    while (fgets(line, MAX, fp) != NULL)   {
	/* �о���� ���ڿ� �߿� �μ��� ���޵� ���ڿ��� ������ ����Ѵ�.*/
        if (strstr(line, argv[1]))  {
                printf("%s", line);
        }
    }

    close(fp);
}

