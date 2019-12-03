#include <stdio.h> 
#include <pthread.h> 
  
// Declaration of thread condition variables 


static int glob = 0 ;

pthread_mutex_t mtx; 
pthread_cond_t cond;
pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_cond_t cond3;
   
// done is a global variable which decides  
// which waiting thread should be scheduled 
int done = 1; 
   
// Thread function 
void *foo(void *n) 
{ 
        int loc,j,s;
        s = pthread_mutex_init(&mtx,NULL);
        while(1) {   

                s = pthread_mutex_lock(&mtx); 
                   
                if (done != (int)*(int*)n) { 

                        if ((int)*(int*)n == 1) { 
                                s = pthread_cond_wait(&cond1, &mtx); 
                        } else if ((int)*(int*)n == 3) { 
                                s = pthread_cond_wait(&cond2, &mtx); 
                        } 
                        else { 
                                s = pthread_cond_wait(&cond3, &mtx); 
                        } 
   
                } 
                // done is equal to n, then print n 
                glob = *(int*)n;
                pthread_cond_signal(&cond);

                // printf("%d  ", *(int*)n); 
                printf("%d ",glob);
   
                // Now time to schedule next thread accordingly  
                // using pthread_cond_signal() 
                if (done == 5) { 
                        done = 1; 
                        s = pthread_cond_signal(&cond1); 

                } 
                else if(done == 1) { 
                        done = 3; 
                        s = pthread_cond_signal(&cond2); 

                } else if (done == 3) { 
                        done = 5; 
                        s = pthread_cond_signal(&cond3); 
                } 
                  
                // Finally release mutex 
                s = pthread_mutex_unlock(&mtx); 
        } 
   
        return NULL; 
} 
  
// Driver code 
int main() 
{ 
        pthread_t  tid1, tid2, tid3; 
        int n1 = 1, n2 = 3, n3 = 5,s; 

        s = pthread_cond_init(&cond,NULL);
          
        // Create 3 threads  
        s = pthread_create(&tid1, NULL, foo, (void *)&n1); 
        s = pthread_create(&tid2, NULL, foo, (void *)&n2); 
        s = pthread_create(&tid3, NULL, foo, (void *)&n3); 
          
        // infinite loop to avoid exit of a program/process 

        int tmp =glob;
        while(1){
            s =  pthread_mutex_lock(&mtx);

            s =  pthread_cond_wait(&cond, &mtx);

            // if(tmp !=glob){

                // printf("%d ",glob);
                // tmp=glob;
            // }

            s =  pthread_mutex_unlock(&mtx);

        }; 
          
        return 0; 
} 
