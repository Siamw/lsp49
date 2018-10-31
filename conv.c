#include <stdio.h>
#include <stdlib.h>

/* 10진수를 2진수로 변환하여 출력하는 프로그램 */
main( int argc, char* argv[] )
{
	int num;
	int i = 0;
	int binary[32];

	num = atoi( argv[1] );           /* 문자열을 숫자로 변환한다. */

	while ( num != 0 ) {             
		binary[i++] = num % 2;   /* 숫자를 2로 나눈 나머지를 저장한다.*/
		num = num/2;
	}

	for( i-=1; i>=0; --i )
		printf("%d", binary[i] ); /* 배열의 마지막 요소부터 출력하여 
					     2진수 형태로 만든다. */
	
	printf("\n");
		
}
	



	
