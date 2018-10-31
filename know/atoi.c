#include <stdio.h>
#include <string.h>

main( int argc, char* argv[] ) 
{
	int len;
	int i = 0;
	int j;
	int num = 0;
	int decimal = 1;
	char arr[10];				/* 정수형으로 변환할 문자열 */

	len =  strlen( argv[1] );		/* 인수로 받은 숫자 문자열의 길이를 구한다.*/
	strcpy( arr, argv[1]);                  /* 변환할 문자열에 인수로 받은 숫자 문자열을
						   복사한다. */

	if ( arr[0] == '-' ) {                  /*  - 부호가 있을 경우  */
		i++;				/* 반복 회수를 1회 감소한다 */
	}

	for( i ; i < len ; i++ )		/*  문장 길이만큼 반복한다. */
	{
		for( j = i; j < len-1 ; j++ )   /*  각각의 자리수에 맞는 10진수의 
		{	                             지수승을 구하기 위한  반복문 */
			decimal *= 10;
			printf("decimal : %d\n", decimal );
		} 
               	num += (decimal * (arr[i]-48) );  /* 숫자 1이 아스키 코드 값으로 49 이므로 
						     48을 빼준 값을 곱해준다. */
		printf("num : %d\n", num );
		decimal = 1;
	}

	if( arr[0] == '-' ) num = num * -1;      /* - 부호가 있는 경우 -1을 곱해준다. */
	printf("Conversion to Integer : %d\n", num );
}
