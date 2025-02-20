#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_PHILOSOPHERS 200

typedef struct s_philosopher
{
    int id;
    pid_t pid;
    long long last_meal;
    int meals_eaten;
} t_philosopher;

sem_t *chopsticks;
sem_t *death_lock;
sem_t *print_lock;
int num_philosophers, time_to_die, time_to_eat, time_to_sleep, must_eat_count = -1;
t_philosopher philosophers[MAX_PHILOSOPHERS];
long long start_time;

long long get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void log_status(int id, char *status)
{
    sem_wait(print_lock);
    printf("[%lld] %d %s\n", get_time_in_ms() - start_time, id, status);
    sem_post(print_lock);
}

void terminate_all()
{
    for (int i = 0; i < num_philosophers; i++)
    {
        kill(philosophers[i].pid, SIGKILL);
    }
    sem_close(chopsticks);
    sem_unlink("/chopsticks");
    sem_close(death_lock);
    sem_unlink("/death_lock");
    sem_close(print_lock);
    sem_unlink("/print_lock");
    exit(0);
}

void philosopher_life(int id)
{
    philosophers[id].last_meal = get_time_in_ms();
    philosophers[id].meals_eaten = 0;

    while (1)
    {
        log_status(id, "is thinking");

        if (get_time_in_ms() - philosophers[id].last_meal > time_to_die)
        {
            sem_wait(death_lock);
            log_status(id, "ÖLDÜ!");
            terminate_all();
        }

        sem_wait(chopsticks);
        sem_wait(chopsticks);
        
        log_status(id, "Yemek yiyor...");
        philosophers[id].last_meal = get_time_in_ms();
        usleep(time_to_eat * 1000);
        philosophers[id].meals_eaten++;

        sem_post(chopsticks);
        sem_post(chopsticks);

        if (must_eat_count != -1 && philosophers[id].meals_eaten >= must_eat_count)
            exit(0);

        log_status(id, "Uyuyor...");
        usleep(time_to_sleep * 1000);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 5 || argc > 6)
    {
        printf("Kullanım: %s <filozof sayısı> <ölüm süresi (ms)> <yemek süresi (ms)> <uyku süresi (ms)> [zorunlu yemek sayısı]\n", argv[0]);
        return (1);
    }

    num_philosophers = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        must_eat_count = atoi(argv[5]);

    if (num_philosophers > MAX_PHILOSOPHERS)
    {
        printf("Maksimum %d filozof destekleniyor.\n", MAX_PHILOSOPHERS);
        return (1);
    }

    chopsticks = sem_open("/chopsticks", O_CREAT, 0644, num_philosophers);
    death_lock = sem_open("/death_lock", O_CREAT, 0644, 1);
    print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
    
    if (chopsticks == SEM_FAILED || death_lock == SEM_FAILED || print_lock == SEM_FAILED)
    {
        printf("Semafor oluşturulamadı!\n");
        return (1);
    }

    start_time = get_time_in_ms();

    for (int i = 0; i < num_philosophers; i++)
    {
        philosophers[i].id = i;
        philosophers[i].pid = fork();
        if (philosophers[i].pid == 0)
        {
            philosopher_life(i);
            exit(0);
        }
        usleep(100);
    }

    for (int i = 0; i < num_philosophers; i++)
        waitpid(philosophers[i].pid, NULL, 0);

    terminate_all();
    return (0);
}
