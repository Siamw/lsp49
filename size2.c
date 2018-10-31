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

        /* dirent 구조체는 i노드 번호와 파일 이름을 변수로
           가지고 있다. */
        struct dirent*  dep;
        struct stat     statbuf;   /* 파일의 상태를 저장하는 구조체 변수*/
	char fileInfo[MAX];
        int i = 0;

	int size = atoi( argv[1]);
 
	if( argc != 2 ) { 
		printf("Usage : %s size\n", argv[0] );
		exit(1);
	}
        
        /* 현재 디렉토리를 연다.*/
        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        /* 디렉토리에 있는 파일의 목록을 읽는다. */
        while( dep = readdir(dp) ) {
                /* '.'와 '..'는 건너뛴다. */
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;

                /* 파일 이름을 fileInfo 배열에 저장한다. */
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
