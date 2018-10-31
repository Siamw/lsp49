#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX 256


main() 
{
        DIR     *dp;
        struct dirent*  dep;
        struct stat     statbuf;
		char fileInfo[MAX];
        int i = 0;
		long int size = 0;
 
        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        while( dep = readdir(dp) ) {
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 ) {
                        continue;
				}
                if( lstat( dep->d_name , &statbuf ) < 0 ) {
                        perror( "lstat");
                        exit(1);
                }

				size += statbuf.st_size; 
		}
		printf("%d bytes \n", size );
	
	closedir(dp);
}

