#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX 256


main( int argc, char* argv[] ) 
{
        DIR     *dp;

        /* dirent ����ü�� i��� ��ȣ�� ���� �̸��� ������
           ������ �ִ�. */
        struct dirent*  dep;
        struct stat     statbuf;   /* ������ ���¸� �����ϴ� ����ü ����*/
	char fileInfo[MAX];
        int i = 0;

	int size = atoi( argv[1]);
 
	if( argc != 2 ) { 
		printf("Usage : %s size\n", argv[0] );
		exit(1);
	}
        
        /* ���� ���丮�� ����.*/
        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        /* ���丮�� �ִ� ������ ����� �д´�. */
        while( dep = readdir(dp) ) {
                /* '.'�� '..'�� �ǳʶڴ�. */
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;

                /* ���� �̸��� fileInfo �迭�� �����Ѵ�. */
                strcpy( fileInfo , dep->d_name );

                if( lstat( fileInfo , &statbuf ) < 0 ) {
                        perror( "lstat");
                        exit(1);
                }

		if ( statbuf.st_size < size ) 
			printf("%s\n", dep->d_name );

	}
	
	closedir(dp);
}
