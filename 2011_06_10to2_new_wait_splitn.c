#include <stdio.h>
#include <stdlib.h>

main( int argc, char* argv[] )
{
        int num;
        int i = 0;
        int binary[32];

        num = atoi( argv[1] );

        while ( num != 0 ) {
                binary[i++] = num % 2;
                num = num/2;
        }

        for( i-=1; i>=0; --i )
                printf("%d", binary[i] );

        printf("\n");
}

// new.c

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

        struct dirent*  dep;
        struct stat     statbuf;
        char            fileInfo[MAX_PATH];
        long            time[MAX_PATH];
        int i = 0;
        long  latest;

if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

       
        while( dep = readdir(dp) ) {
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;

                strcpy( fileInfo , dep->d_name );

                if( lstat( fileInfo , &statbuf ) < 0 ) {
                        perror( "lstat");
                        exit(1);
                }

                /* print_time( statbuf.st_mtime ); */
                time[i++] = statbuf.st_mtime;
	}

        closedir(dp);

	//at time, 
        latest = time[--i];


        for( i-=1 ; i>=0; --i )
             if ( time[i] > latest )
                  latest = time[i];


        if(  ( dp = opendir(".") ) == NULL ) {
                perror( "opendir");
                exit(0);
        }

        while( dep = readdir(dp) ) {
                if( strcmp ( dep->d_name, "." ) == 0 ||
                                 strcmp( dep->d_name , "..") == 0 )
                        continue;
	  
                strcpy( fileInfo , dep->d_name );

                if( lstat( fileInfo , &statbuf ) < 0 ) {
                        perror( "lstat");
                        exit(1);
                }

                if( latest == statbuf.st_mtime )
                {
                        printf("%s\n",  dep->d_name );
                        break;
                }
        }

        closedir( dp );
}

// wait.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
        pid_t   pid;
        int             status;

        if ((pid = fork()) < 0)  {
                perror("fork");
                exit(1);
        }
        else if (pid == 0)  {
                printf("I'm a child\n");
                sleep(2);
        }
        else  {
                waitpid( pid,  &status, WUNTRACED );
                printf("A child killed with %d status\n", status);
         } 
}


// splitn.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_BUF 256

long
filesize(FILE *fp)
{
        long    cur, size;

        cur = ftell(fp);        
                                

        fseek(fp, 0L, SEEK_END);    
        size = ftell(fp);           
        fseek(fp, cur, SEEK_SET);   
                                   
        return(size);
}

main(int argc, char *argv[])
{
        FILE    *src;
        char    buf[MAX_BUF];
        int     count, size;
        int     divide;
        int     *fd;
        int      i;
        char    fileName[13] = "./";
        char    newFile[13] = "./";
        char    fileNum[2];
        int     total;

        if (argc != 3)  {
                fprintf( stderr, "Usage: %s source count\n", argv[0]);
                exit(1);
        }
	

	divide = atoi( argv[2] );       // 나누어질 파일의 개수를 int형으로 변환

        strcat( fileName, argv[1] );

        printf("divide = %d\n", divide );
        printf("fileName = %s\n", fileName );

        fd = (int*) malloc ( sizeof(int) * divide );

        if ( (src = fopen( argv[1], "rb")) == NULL )  {
                perror("fopen");
                exit(1);
        }


        size  = filesize(src);             // 파일의 크기
        count = size / divide;             // 나누어질 파일 각각의 크기


	printf("size : %d\n", size );

        for( i = 0 ;  i < divide-1 ; ++i )
        {
             strcpy( newFile, fileName );
             sprintf( fileNum , "%d", i+1 );
             strcat ( newFile , fileNum );

             printf( "new file name : %s\n", newFile );

         
             if (  ( fd[i] =  creat( newFile , 0755 ) ) < 0 )  {
                        perror("creat");
                        exit(1);
             }

           
             fread(buf, 1,count, src);
	
             write( fd[i], buf, count );

        }

        strcpy( newFile, fileName );
        sprintf( fileNum , "%d", i+1 );
        strcat ( newFile , fileNum );
        printf("new file name : %s\n", newFile );
        fd[i] =  creat( newFile, 0755  );

        while ( ( count = fread(buf, 1, MAX_BUF, src) ) > 0)  {
                printf("Read count : %d\n", count );
                write( fd[i],buf, count  );
        }

        fclose(src);


        for( i = 0;  i < divide ; ++i )
                close( fd[i] );

        free( fd );
}


