#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>


#define SEM_NAME "/sems"
#define SEM_NUM 5


int main(void)
{
	sem_t *sem;
	pid_t pid;
	int i;

	i = 0;

	sem = sem_open(SEM_NAME, O_CREAT, 0644, 3);
	if (sem == SEM_FAILED)
	{
		printf("semaphore couldn't created\n");
		return (0);
	}

	while (i < SEM_NUM)
	{
		pid = fork();
		if (pid < 0)
			return (printf("fork failed\n"));
		if (pid == 0)
		{
			printf("Müşteri %d mekana intikal etti\n", i+1);
			sem_wait(sem);
			printf("Müşteri %d masaya oturdu ve yemek yiyor\n", i+1);
			sleep(5);
			printf("Müşteri %d yemeğini yedi şimdi gidiyor\n", i+1);
			sem_post(sem);
			exit(0);
		}
		sleep(1);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		wait(NULL);
		i++;
	}
	sem_close(sem);
	sem_unlink(SEM_NAME);

	return (0);
}
