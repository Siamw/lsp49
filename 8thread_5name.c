#include <stdio.h>
#include <pthread.h>

#define	  MAX	5 

struct threadStruct {   
	char cnt[2];   
	char name[10];  
};

void threadFunc(struct threadStruct* data) { 

	printf("Thread %s: %s\n", data->cnt, data->name );

}



main() {
	pthread_t tid[MAX];
	int i;
	
	struct threadStruct th[5]={
		{"1", "kim"},
		{"2", "lee"},
		{"3", "park"},
		{"4", "choi"},
		{"5", "hong"}
	};
	
	for( i = 0; i < MAX; i++ )  { 
		if( pthread_create( &tid[i], NULL, (void*)threadFunc, (void*)&th[i] ) < 0 )
		{
			perror("pthread_create");
			exit(1);
		}
	} 
	
	for( i = 0; i < MAX; ++i )  { 
		pthread_join(  tid[i], NULL );      /* 해당 ID의 쓰레드가 종료하기를 기다린다.*/
	} 

}
