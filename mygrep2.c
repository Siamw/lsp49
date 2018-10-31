#include <stdio.h>


main(int argc, char * argv[])
{
    FILE    *fp;
    char    line[1024], word[128];
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

    while (fgets(line, 1024, fp) != NULL)   {
        if (strstr(line, argv[1]))  {
                printf("%s", line);
        }
    }

    close(fp);
}

