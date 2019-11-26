#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>

sem_t *mutex;

int count=0;

void *inc(void *arg){
	int id=(int *)arg;
	int i=0;
	sem_wait(mutex);
	for(i=0; i<10; i++){
		printf("thread%d(+1), count = %d\n", id,count);
		count++;
	}
	sem_post(mutex);	

	pthread_exit(NULL);
}

void *dec(void *arg){
	int id=(int *)arg;
	int i=0;
	sem_wait(mutex);
	for(i=0; i<10; i++){
		printf("thread%d(-1), count = %d\n", id,count);
		count--;
	}
	sem_post(mutex);	
	pthread_exit(NULL);
}

int main()
{
	mutex = sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 1);

	pthread_t id[4];
	pthread_create(&id[0], NULL, dec, (void *)0);
	pthread_create(&id[1], NULL, inc, (void *)1);
	pthread_create(&id[2], NULL, dec, (void *)2);
	pthread_create(&id[3], NULL, inc, (void *)3);

	int i=0;
	for(i=0; i<4; i++){
		pthread_join(id[i], NULL);
	}
	
	printf("\noutput is %d\n", count);
	sem_close(mutex);
	sem_unlink("/mysem");
	pthread_exit(NULL);
	return 0;
}
