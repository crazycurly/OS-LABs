#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int result=0;
void *child(void *arg){
	int *input = (int *) arg;
	// int *result =malloc(sizeof(int) *1);
	result=input[0]+input[1];
	int i=1;
	while(1){
		sleep(1);
		printf("sleep :%d\n",i );
		i++;
	}
	// pthread_exit((void *)result);
}

int main()
{
	pthread_t t;
	void *ret;
	int input[2]={1,2};

	pthread_create(&t,NULL,child,(void*)input);

	sleep(4);
	pthread_cancel(t);
	// pthread_join(t,&ret);

	// int *result =(int *)ret;

	printf("%d +%d =%d\n",input[0],input[1],result);
	
	return 0;
}