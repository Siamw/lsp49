#include <stdio.h>

main( int argc, char* argv[] ) 
{
	char op[2];

	if( argc != 4 ) {
		printf("Usage: %s number operator number\n", argv[0] );
		exit(1);
	}
	
	strcpy( op, argv[2]);


	if( !strcmp( op, "+") ){
		printf("%d\n", atoi(argv[1])+atoi(argv[3]) );
        } 
	else if( !strcmp( op, "-") ) { 
		printf("%d\n", atoi(argv[1])-atoi(argv[3]) );
	}
	else if( !strncmp( op, "x", 1) ) {
		printf("%d\n", atoi(argv[1])*atoi(argv[3]) );
	}
	else if ( !strcmp( op, "/" ) ) { 
		printf("%d\n", atoi(argv[1])/atoi(argv[3]) );
	}
	
}

