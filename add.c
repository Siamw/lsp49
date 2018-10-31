#include <stdio.h>

main ( int argc, char* argv[] )
{
	if( argc != 3 )
	{	
		printf( " " );
	}
	
	printf("%d\n", atoi(argv[1]) + atoi(argv[2]) );
	
}
