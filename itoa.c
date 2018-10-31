#include <stdio.h>
#include <string.h>

char* itoA( int num, char* str );


int main()
{
	int num = 3840;
	char str[10];

	itoA( num, str );

	printf("String : %s\n" , str );

}

char* itoA( int num, char* str ) 
{
	int value;
	int     i = 0; 
	int     j = 0;
	char    temp[12];

	value = num;

	while ( value != 0 ) { 
		temp[i] = ( value % 10 ) + '0';
		printf("temp[%d] : %d\n", i, temp[i] );
		value = value / 10;
		i++;	
		printf("value    : %d\n", value );
	}
	
	temp[i] = '\0';
	printf("temp : %s\n", temp );
	
	for( j = i-1; j >= 0 ; j-- ) 
	{
		str[i-j-1] = temp[j];
	}
	
	str[i] = '\0';
	
	return str;

}
