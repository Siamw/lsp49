#include <stdio.h>
#include <stdlib.h>

/* 10������ 2������ ��ȯ�Ͽ� ����ϴ� ���α׷� */
main( int argc, char* argv[] )
{
	int num;
	int i = 0;
	int binary[32];

	num = atoi( argv[1] );           /* ���ڿ��� ���ڷ� ��ȯ�Ѵ�. */

	while ( num != 0 ) {             
		binary[i++] = num % 2;   /* ���ڸ� 2�� ���� �������� �����Ѵ�.*/
		num = num/2;
	}

	for( i-=1; i>=0; --i )
		printf("%d", binary[i] ); /* �迭�� ������ ��Һ��� ����Ͽ� 
					     2���� ���·� �����. */
	
	printf("\n");
		
}
	



	
