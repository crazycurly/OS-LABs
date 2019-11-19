#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
	pid_t new_pid;

	unsigned int seconds = 3;
	void sig_alrm(int signo)
	{
		printf("recived SIGALRM\n");
		printf("%d\n",getppid() );
		kill(getppid(),SIGTERM); // I don't know what the fuck but it will create a process with parent id +1 
	}


	if(fork()){
		printf("Child process\n");
		printf("Pid: %d\t, Parent pid: %d\n", getpid(), getppid());
		signal(SIGALRM, sig_alrm);
		alarm(seconds);
		pause();
	}
	else{
		printf("Parent process\n");
		printf("Pid: %d\t", getpid());
		while(1);
	}

	printf("%d exit\n",getpid());



	return 0;
}