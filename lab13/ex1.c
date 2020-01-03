#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0 ;

pthread_mutex_t mtx;

static void *threadFunc_add(void *arg){
	int loops = *((int *)arg);
	int loc,j,s;
	printf("loops = %d\n",loops);

	s = pthread_mutex_init(&mtx,NULL);
	for (int i = 0; i < loops; ++i)
	{
		s = pthread_mutex_lock(&mtx);

		loc = glob ;
		loc+=2;
		glob = loc;
		printf("G+ = %d\n",glob);


		s = pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

static void *threadFunc_sub(void *arg){
	int loops = *((int *)arg);
	int loc,j,s;
	printf("loops = %d\n",loops);

	s = pthread_mutex_init(&mtx,NULL);
	for (int i = 0; i < loops; ++i)
	{
		s = pthread_mutex_lock(&mtx);

		loc = glob ;
		loc-=2;
		glob = loc;
		printf("G- = %d\n",glob);

		s = pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main(int argc, char  *argv[])
{
	pthread_t t1,t2,t3;
	int loops,s;

	loops = atoi(argv[1]);

	s = pthread_create(&t1,NULL,threadFunc_add,&loops);
	s = pthread_create(&t2,NULL,threadFunc_add,&loops);
	s = pthread_create(&t3,NULL,threadFunc_sub,&loops);
	

	s = pthread_join(t1,NULL);
	s = pthread_join(t2,NULL);
	s = pthread_join(t3,NULL);

	printf("glob = %d\n",glob);

	s = pthread_mutex_destroy(&mtx);
    return 0;
}
