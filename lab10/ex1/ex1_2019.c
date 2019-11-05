#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static __thread int glob = 0;

void *function(void *arg){
	int loops=(int *)arg;
	int loc,j;
	for(j=0;j< loops;j++){
		loc = glob;
		loc++;
		glob=loc;
	}
	printf("thread_ID = %lu , glob = %d\n",pthread_self(),glob);
	pthread_exit(NULL);
}

int main(){
	pthread_t id[2];
	pthread_create(&id[0],NULL, function, (void *)100);
	pthread_create(&id[1],NULL, function, (void *)50);

	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);

	printf("(main thread)glob value after running 2 thread : %d\n",glob);

	return 0;
}


 


