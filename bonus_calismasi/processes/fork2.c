#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	pid_t pid1;
	pid_t pid2;

	printf("parent process id = %d\nParent'in parenti (terminal) = %d\n", getpid(), getppid());

	pid1 = fork();
	if (pid1 == 0)
		return(printf("getpid of child 1 = %d\ngetpid of child1's parent = %d\n", getpid(), getppid()), 0);
		 
	pid2 = fork();
	if (pid2 == 0)
		return(printf("getpid of child2 = %d\ngetpid of child2's parent = %d\n", getpid(), getppid()), 0);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
