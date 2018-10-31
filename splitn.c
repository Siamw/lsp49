#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_BUF 256

long
filesize(FILE *fp)
{
        long    cur, size;

        cur = ftell(fp);        // 스트림의 현재 파일 포인터를 조사한다.
                                // 조사된 파일 포인터는 파일의 시작점
                                // 에서부터의 거리를 바이트 단위로
                                // 표시한 것이다.

        fseek(fp, 0L, SEEK_END);    // 인수로 전달된  파일 포인터를
                                    // 파일의 끝으로 이동한다.
        size = ftell(fp);           // 현재 파일 포인터를 조사한다.
        fseek(fp, cur, SEEK_SET);   // 파일의 처음에서 cur 만큼 떨어진
                                    // 곳으로 파일 포인터를 이동한다.
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
	
	divide = atoi( argv[2] );	// 나누어질 파일의 개수를 int형으로 변환
	
	strcat( fileName, argv[1] );     
	
	printf("divide = %d\n", divide );
	printf("fileName = %s\n", fileName );  /* 파일명에 './' 추가 */

	fd = (int*) malloc ( sizeof(int) * divide );   /* 나누어질 파일 개수만큼 파일
							  디스크립터를 저장하는 공간 할당*/		
											
	/* 원본 파일을 읽기 모드로 연다 */
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
             strcat ( newFile , fileNum );     /* 생성된 파일의 이름을 붙인다 */
		
	     printf( "new file name : %s\n", newFile );
	    
	     /* create 함수는 이미 존재하는 파일의 경우에는 초기화(사이즈 0)
		시키거나 존재하지 않는 파일을 새로 생성할 때 사용된다. 
		첫번째 인수에는 경로, 두번째 인수에는 접근 권한이 들어가고 
		실행 오류시 -1을 리턴한다. */
	     if (  ( fd[i] =  creat( newFile , 0755 ) ) < 0 )  { 
			perror("creat");
			exit(1);
	     }
	     
             // 1바이트 크기의 메모리 블록을 count개 만큼
             // 파일로부터 읽어들인다.
             fread(buf, 1,count, src);
	
             /* buf에 있는 내용을 count 길이만큼 파일에 복사한다. */
             write( fd[i], buf, count );

        }

        strcpy( newFile, fileName );
        sprintf( fileNum , "%d", i+1 );
        strcat ( newFile , fileNum ); 
	printf("new file name : %s\n", newFile );

	/* 원본에 남아있는 내용을 파일에 출력하기 위해 하나의 파일을 더 연다. */
	fd[i] =  creat( newFile, 0755  );
	
	/* 원본 파일에 남아있는 내용을 파일에 출력한다. */
        while ( ( count = fread(buf, 1, MAX_BUF, src) ) > 0)  {
		printf("Read count : %d\n", count ); 
                write( fd[i],buf, count  );
        }

        fclose(src);
	
	/* 파일을 닫는다. */
	for( i = 0;  i < divide ; ++i )
		close( fd[i] );

	free( fd );

}


