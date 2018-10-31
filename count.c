#include <stdio.h>


int main( int argc, char* argv[] )
{
	FILE	*src;
	char    ch;
	int     count = 0;

	if( argc != 2 ) {
		printf("Usage: %s source\n", argv[0] );
		exit(1);
	}

	if( ( src = fopen( argv[1], "rt") ) == NULL ) { 
		perror("fopen");
		exit(1);
	}	
	
	while( ( ch = fgetc(src) ) != EOF ) {

		if( ch >= 'a' && ch <= 'z' ) 
			count++;
	}
			
	fclose ( src );

	printf("Alphabet Count : %d\n", count );

	return 0;
}	
		
  

