#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_fork
{
	sem_t				*fork;
} t_fork;

typedef struct s_philo
{
	int					id;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					is_dead;
	int					eat_count;
} t_philo;

typedef struct s_data
{
	long long			begin_time;
	int					philo_num;
	t_philo				*philos;	
}	t_data;

#endif