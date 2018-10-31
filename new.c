#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 256



main()
{
        DIR     *dp;

        /* dirent 구조체는 i노드 번호와 파일 이름을 변수로
           가지고 있다. */
        struct dirent*  dep;
        struct stat     statbuf;   /* 파일의 상태를 저장하는 구조체 변수*/
        char            fileInfo[MAX_PATH];
	long            time[MAX_PATH];
	int i = 0;
	long  latest;
	

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

		/* print_time( statbuf.st_mtime ); */
		/* 파일 변경 시각을 time 배열에 저장한다. */
		time[i++] = statbuf.st_mtime; 
		
	}	
	
	closedir(dp);
	
	latest = time[--i];

	/* 최대값(=즉, 가장 최근의 파일 ) 을 구하는 루프 */
	for( i-=1 ; i>=0; --i )
	     if ( time[i] > latest ) 
		  latest = time[i];	

	/* 다시 디렉토리를 연다 */
        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        while( dep = readdir(dp) ) {
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;

                /* 파일 이름을 fileInfo 배열에 저장한다. */
                strcpy( fileInfo , dep->d_name );

                if( lstat( fileInfo , &statbuf ) < 0 ) {
                        perror( "lstat");
			exit(1);
		}
	
		/* latest 와 파일의 최종 변경 시각을 비교하여 
		   일치하면 그 파일명을 출력한다. */
		if( latest == statbuf.st_mtime ) 
		{	
			printf("%s\n",  dep->d_name );	
			break;
		}
        }	 

	closedir( dp );

}


