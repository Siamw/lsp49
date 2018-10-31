#include <stdio.h>
#include <pthread.h>

/* 새롭게 생성되어 실행될 서브 스레드 모듈 */
void subThread( void )
{
	/* 서브 스레드의 번호 출력 */
	int subThID = pthread_self();
	printf("서브 스레드 번호: %d\n", subThID);
	
	/* 서브 스레드 작업 : 메초마다 메시지 출력 */
	while ( 1) {
		sleep(1);
		printf("서브 스레드 동작중!\n");
	}
}

main()
{
	pthread_t subTh_t;
	
	int mainThID = pthread_self();
	
	printf("메인 스레드 번호 : %d\n", mainThID );
	
	if ( pthread_create( &subTh_t, NULL, (void*)subThread, NULL ) )
	{
		perror("pthread_create");
		exit(1);
	}
	
	printf("메인스레드는 종료. 서브스레드 ID : %d\n", subTh_t );
	pthread_exit(0);
		

}



