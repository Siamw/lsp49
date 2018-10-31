#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main( int argc, char* argv[] ) 
{
	struct stat	statbuf;        /* 파일의 정보를 저장할 stat 구조체 */
	
	if( argc != 2 ) { 
		printf("Usage : %s source\n", argv[0] );
		exit(1);
	}
	
	/*  명령행 인수로 전달된 파일의 정보를 읽어온다. */
	if( stat( argv[1], &statbuf ) < 0 ) {
		perror("stat");
		exit(1);
	}
	
	/* chmod 시스템 콜을 사용하여 모드를 변경한다. 
	   GROUP과 OTHER의 write 권한을 제거하고 execute 권한을 추가한다.*/
	if( chmod ( argv[1], ( statbuf.st_mode & ~S_IWGRP & ~S_IWOTH ) | 
				S_IXGRP | S_IXOTH ) < 0 )  { 
		perror( "chmod");
		exit(1);
	}
	
	
}
		
		












