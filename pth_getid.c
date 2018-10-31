#include <stdio.h>
#include <pthread.h>

/* ���Ӱ� �����Ǿ� ����� ���� ������ ��� */
void subThread( void )
{
	/* ���� �������� ��ȣ ��� */
	int subThID = pthread_self();
	printf("���� ������ ��ȣ: %d\n", subThID);
	
	/* ���� ������ �۾� : ���ʸ��� �޽��� ��� */
	while ( 1) {
		sleep(1);
		printf("���� ������ ������!\n");
	}
}

main()
{
	pthread_t subTh_t;
	
	int mainThID = pthread_self();
	
	printf("���� ������ ��ȣ : %d\n", mainThID );
	
	if ( pthread_create( &subTh_t, NULL, (void*)subThread, NULL ) )
	{
		perror("pthread_create");
		exit(1);
	}
	
	printf("���ν������ ����. ���꽺���� ID : %d\n", subTh_t );
	pthread_exit(0);
		

}



