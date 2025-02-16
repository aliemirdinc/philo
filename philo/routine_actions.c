/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:33:18 by aldinc            #+#    #+#             */
/*   Updated: 2025/02/09 17:40:48 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Think routine funtion

void	think(t_philo *philo)
{
	ft_printf(philo, "is thinking");
}

// Dream routine funtion

void	dream(t_philo *philo)
{
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

// Eat routine funtion

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_printf(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_printf(philo, "has taken a fork");
	philo->eating = 1;
	ft_printf(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
