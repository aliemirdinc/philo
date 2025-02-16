/*
			orphan process nedir
			Öksüz yetim derbeder olmuş mazlum processtir
			anası babası yoktur
			terk edilmiştir...
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid1;

	printf("main pid = %d\n", getpid());
	pid1 = fork();
	if (pid1 == 0)
	{
		sleep(1);
		printf("getpid = %d\n", getpid());
		printf("AAA BABA, GERİ DÖNMÜŞSÜN getppid = %d\n", getppid());
		return (0);
	}
	else
	{
		printf("TERK EDMEM COCUUMU BEN BABAYIM ULAN getpid = %d\n", getpid());
		printf("getppid = %d\n", getppid());
		waitpid(pid1, NULL, 0);
		return (0);
	}
	

}