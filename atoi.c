#include <stdio.h>
#include <string.h>

main( int argc, char* argv[] ) 
{
	int len;
	int i = 0;
	int j;
	int num = 0;
	int decimal = 1;
	char arr[10];				/* ���������� ��ȯ�� ���ڿ� */

	len =  strlen( argv[1] );		/* �μ��� ���� ���� ���ڿ��� ���̸� ���Ѵ�.*/
	strcpy( arr, argv[1]);                  /* ��ȯ�� ���ڿ��� �μ��� ���� ���� ���ڿ���
						   �����Ѵ�. */

	if ( arr[0] == '-' ) {                  /*  - ��ȣ�� ���� ���  */
		i++;				/* �ݺ� ȸ���� 1ȸ �����Ѵ� */
	}

	for( i ; i < len ; i++ )		/*  ���� ���̸�ŭ �ݺ��Ѵ�. */
	{
		for( j = i; j < len-1 ; j++ )   /*  ������ �ڸ����� �´� 10������ 
		{	                             �������� ���ϱ� ����  �ݺ��� */
			decimal *= 10;
			printf("decimal : %d\n", decimal );
		} 
               	num += (decimal * (arr[i]-48) );  /* ���� 1�� �ƽ�Ű �ڵ� ������ 49 �̹Ƿ� 
						     48�� ���� ���� �����ش�. */
		printf("num : %d\n", num );
		decimal = 1;
	}

	if( arr[0] == '-' ) num = num * -1;      /* - ��ȣ�� �ִ� ��� -1�� �����ش�. */
	printf("Conversion to Integer : %d\n", num );
}
