#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	printf("before fork pid = %d\n", getpid());

	pid_t pid = fork();

	if (pid < 0)
		return (printf("fork failed to exist\n"), 1);

	else if(pid == 0)
	{
		sleep(2);
		printf("Child process PID = %d\n", getpid());
		printf("(child içinde)Parent process PID = %d\n", getppid());
		printf("(child) pid value = %d\n", pid);
		return (0);
		
	}
	else if (pid > 0)
	{
		printf("we are in now parent process and the PID of parent = %d\n", getpid());
		printf("(parent içinde)Parent'in parenti ??? PID = %d\n", getppid());
		printf("(child) getpid value = %d\n", pid);
		//waitpid(pid, NULL, 0);
		//printf("Child process finished, Parent continues\n");
		return (0);
	}
}
