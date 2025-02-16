#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	pid_t pid1;
	pid_t pid2;
	pid_t pid3;
	pid_t pid4;

	printf("main parent process id = %d\nParent'in parenti (terminal) = %d\n", getpid(), getppid());

	pid1 = fork();
	if (pid1 == 0)
	{
		printf("getpid of child 1(pid1) = %d\ngetpid of child1's parent = %d\n", getpid(), getppid());
		pid3 = fork();
		if (pid3 == 0)
		{
			printf("now we are in the pid1's child, pid3 = %d\n", getpid());
			printf("pid3's parent = %d\n\n", getppid());
			return (0);
		}
		waitpid(pid3, NULL, 0);
		return(0);
	}
		 
	pid2 = fork();
	if (pid2 == 0)
	{
		printf("getpid of child2(pid2) = %d\ngetpid of child2's parent = %d\n", getpid(), getppid());
		pid4 = fork();
		if (pid4 == 0)
		{
			printf("now we are in the pid2's child, pid4 = %d\n", getpid());
			printf("pid4's parent = %d\n\n", getppid());
			return (0);
		}
		waitpid(pid4, NULL, 0);
		return(0);
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
