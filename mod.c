#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main( int argc, char* argv[] ) 
{
	struct stat	statbuf;        /* ������ ������ ������ stat ����ü */
	
	if( argc != 2 ) { 
		printf("Usage : %s source\n", argv[0] );
		exit(1);
	}
	
	/*  ����� �μ��� ���޵� ������ ������ �о�´�. */
	if( stat( argv[1], &statbuf ) < 0 ) {
		perror("stat");
		exit(1);
	}
	
	/* chmod �ý��� ���� ����Ͽ� ��带 �����Ѵ�. 
	   GROUP�� OTHER�� write ������ �����ϰ� execute ������ �߰��Ѵ�.*/
	if( chmod ( argv[1], ( statbuf.st_mode & ~S_IWGRP & ~S_IWOTH ) | 
				S_IXGRP | S_IXOTH ) < 0 )  { 
		perror( "chmod");
		exit(1);
	}
	
	
}
		
		












