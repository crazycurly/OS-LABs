#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sem_t sem;
int count=0;

void *inc(void *arg){
	int id=(int *)arg;
	int i=0;
	
	for(i=0; i<10; i++){
		sem_wait(&sem);
		printf("thread%d(+1), count = %d\n", id,count);
		count++;
		sem_post(&sem);
	}
	pthread_exit(NULL);
}

void *dec(void *arg){
	int id=(int *)arg;
	int i=0;
	for(i=0; i<10; i++){
		sem_wait(&sem);
		printf("thread%d(-1), count = %d\n", id,count);
		count--;
		sem_post(&sem);
	}
	pthread_exit(NULL);
}

int main(void){
	sem_init(&sem, 0, 1);
	
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
	sem_destroy(&sem);
	pthread_exit(NULL);
}