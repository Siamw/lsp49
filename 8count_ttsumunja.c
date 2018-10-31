#include <stdio.h>

main(int argc, char * argv[])
{
    int count = 0;
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
        if ( c >= '!' && c <= '/'){
            count++;
        }
		if ( c >= ':' && c <= '@'){
			count++;
		}
		if ( c >= '[' && c <= '?'){
			count++;
		}
		if ( c >= '{' && c <= '~'){
			count++;
		}

    }

    printf("%d\n", count);

    close(fp);
}
