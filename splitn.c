#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_BUF 256

long
filesize(FILE *fp)
{
        long    cur, size;

        cur = ftell(fp);        // ��Ʈ���� ���� ���� �����͸� �����Ѵ�.
                                // ����� ���� �����ʹ� ������ ������
                                // ���������� �Ÿ��� ����Ʈ ������
                                // ǥ���� ���̴�.

        fseek(fp, 0L, SEEK_END);    // �μ��� ���޵�  ���� �����͸�
                                    // ������ ������ �̵��Ѵ�.
        size = ftell(fp);           // ���� ���� �����͸� �����Ѵ�.
        fseek(fp, cur, SEEK_SET);   // ������ ó������ cur ��ŭ ������
                                    // ������ ���� �����͸� �̵��Ѵ�.
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
	
	divide = atoi( argv[2] );	// �������� ������ ������ int������ ��ȯ
	
	strcat( fileName, argv[1] );     
	
	printf("divide = %d\n", divide );
	printf("fileName = %s\n", fileName );  /* ���ϸ� './' �߰� */

	fd = (int*) malloc ( sizeof(int) * divide );   /* �������� ���� ������ŭ ����
							  ��ũ���͸� �����ϴ� ���� �Ҵ�*/		
											
	/* ���� ������ �б� ���� ���� */
        if ( (src = fopen( argv[1], "rb")) == NULL )  {
                perror("fopen");
                exit(1);
        }


	size  = filesize(src);             // ������ ũ�� 
        count = size / divide;             // �������� ���� ������ ũ�� 

	printf("size : %d\n", size );

	for( i = 0 ;  i < divide-1 ; ++i )
	{
             strcpy( newFile, fileName );
	     sprintf( fileNum , "%d", i+1 );    
             strcat ( newFile , fileNum );     /* ������ ������ �̸��� ���δ� */
		
	     printf( "new file name : %s\n", newFile );
	    
	     /* create �Լ��� �̹� �����ϴ� ������ ��쿡�� �ʱ�ȭ(������ 0)
		��Ű�ų� �������� �ʴ� ������ ���� ������ �� ���ȴ�. 
		ù��° �μ����� ���, �ι�° �μ����� ���� ������ ���� 
		���� ������ -1�� �����Ѵ�. */
	     if (  ( fd[i] =  creat( newFile , 0755 ) ) < 0 )  { 
			perror("creat");
			exit(1);
	     }
	     
             // 1����Ʈ ũ���� �޸� ����� count�� ��ŭ
             // ���Ϸκ��� �о���δ�.
             fread(buf, 1,count, src);
	
             /* buf�� �ִ� ������ count ���̸�ŭ ���Ͽ� �����Ѵ�. */
             write( fd[i], buf, count );

        }

        strcpy( newFile, fileName );
        sprintf( fileNum , "%d", i+1 );
        strcat ( newFile , fileNum ); 
	printf("new file name : %s\n", newFile );

	/* ������ �����ִ� ������ ���Ͽ� ����ϱ� ���� �ϳ��� ������ �� ����. */
	fd[i] =  creat( newFile, 0755  );
	
	/* ���� ���Ͽ� �����ִ� ������ ���Ͽ� ����Ѵ�. */
        while ( ( count = fread(buf, 1, MAX_BUF, src) ) > 0)  {
		printf("Read count : %d\n", count ); 
                write( fd[i],buf, count  );
        }

        fclose(src);
	
	/* ������ �ݴ´�. */
	for( i = 0;  i < divide ; ++i )
		close( fd[i] );

	free( fd );

}


