/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:33:00 by aldinc            #+#    #+#             */
/*   Updated: 2025/02/11 16:27:25 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks that the input is only numbers

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

// Checks if the program input is correct

int	check_valid_args(char **argv)
{
	if (ft_atol(argv[1]) > PHILO_MAX || ft_atol(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (printf("Invalid philosophers number\n"), 1);
	if (ft_atol(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (printf("Invalid time to die\n"), 1);
	if (ft_atol(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (printf("Invalid time to eat\n"), 1);
	if (ft_atol(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (printf("Invalid time to sleep\n"), 1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (printf("Invalid number of times per eat\n"), 1);
	return (0);
}
// Main function

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (printf("Wrong argument count\n"), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destory_all(NULL, &program, forks);
	return (0);
}
