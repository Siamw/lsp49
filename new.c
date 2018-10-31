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

        /* dirent ����ü�� i��� ��ȣ�� ���� �̸��� ������
           ������ �ִ�. */
        struct dirent*  dep;
        struct stat     statbuf;   /* ������ ���¸� �����ϴ� ����ü ����*/
        char            fileInfo[MAX_PATH];
	long            time[MAX_PATH];
	int i = 0;
	long  latest;
	

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

		/* print_time( statbuf.st_mtime ); */
		/* ���� ���� �ð��� time �迭�� �����Ѵ�. */
		time[i++] = statbuf.st_mtime; 
		
	}	
	
	closedir(dp);
	
	latest = time[--i];

	/* �ִ밪(=��, ���� �ֱ��� ���� ) �� ���ϴ� ���� */
	for( i-=1 ; i>=0; --i )
	     if ( time[i] > latest ) 
		  latest = time[i];	

	/* �ٽ� ���丮�� ���� */
        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        while( dep = readdir(dp) ) {
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;

                /* ���� �̸��� fileInfo �迭�� �����Ѵ�. */
                strcpy( fileInfo , dep->d_name );

                if( lstat( fileInfo , &statbuf ) < 0 ) {
                        perror( "lstat");
			exit(1);
		}
	
		/* latest �� ������ ���� ���� �ð��� ���Ͽ� 
		   ��ġ�ϸ� �� ���ϸ��� ����Ѵ�. */
		if( latest == statbuf.st_mtime ) 
		{	
			printf("%s\n",  dep->d_name );	
			break;
		}
        }	 

	closedir( dp );

}


