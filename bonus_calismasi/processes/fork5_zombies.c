#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();  // Yeni bir çocuk süreç oluştur

    if (pid == 0) // Çocuk süreç
    {
        printf("🧒 Çocuk süreç (PID: %d) görevini tamamlıyor...\n", getpid());
        exit(0);  // Çocuk hemen bitiyor
    }
    else // Ebeveyn süreç
    {
        printf("👑 Ebeveyn süreç (PID: %d) uyuyor...\n", getpid());
        sleep(10);  // Çocuk sürecin çıkışını almadığı için o zombi olacak!
		waitpid(pid, NULL, 0);
		printf("uyuyom ama wait de var\n");
		sleep(10);
    }

    return 0;
}
