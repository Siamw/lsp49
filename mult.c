#include <stdio.h>

main( int argc, char* argv[] ) 
{
	if( argc != 3 ) {
		printf("Usage : %s integer integer\n", argv[0] );
		exit(1);
	}

	printf("%d\n", atoi(argv[1]) * atoi(argv[2]) );
	
}
	



	

