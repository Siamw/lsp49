#include <stdio.h>

#define ON  1
#define OFF 0

main( int argc, char* argv[] ) 
{
	char ch;
	FILE* src;
	int countCh = 0;
	int countLine = 0;
	int countWord = 0;
	int flag;

	if ( argc != 2 ) {
		printf("Usage : %s fileName\n", argv[0] );
		exit(1);
	}

	if ( ( src = fopen( argv[1], "rb" ) )  == NULL ) {
		perror("fopen");
		exit(1);
	}

	while( ( ch = fgetc(src) ) != EOF )  { 
		countCh++;                     /* ���� �� ���� */
	
		if ( ch == ' ' || ch == '\n' || ch == '\t') 
			flag = ON;
		else { 
			if( flag == ON )       /* �ܾ� �� ���� */ 
		  	      countWord++;

			 flag = OFF;
		}
		
		if( ch == '\n' )	       /* ���� �� ���� */
			countLine++;
	}
	
	printf("Number of character : %d\n", countCh);	
	printf("Number of words : %d\n", countWord );	
	printf("Number of lines : %d\n", countLine );	
	
	close( src );
}
