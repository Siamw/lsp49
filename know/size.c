#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main( int argc, char* argv[] )
{
	struct stat	statbuf;
	
	if( argc != 2 ) { 
		printf("Usage : %s source\n" , argv[0] );
	}
	
	if( lstat( argv[1] , &statbuf ) ) {
		perror( "lstat");
		exit(1);
	}
	
	printf("File size : %d\n", statbuf.st_size );
	
}

