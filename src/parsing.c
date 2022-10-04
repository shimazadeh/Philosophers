/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:23:57 by shabibol          #+#    #+#             */
/*   Updated: 2022/10/04 19:23:58 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	argument_check(char **av, int ac)
{
	int				i;
	long long int	num;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("invalid number of arguments\n"), -1);
	if (av[1] == 0)
		return (printf("invalid number of philosophers\n"), -1);
	while (av[i])
	{
		if (ft_is_num(av[i]) < 0)
			return (printf("invalid argument value\n"), -1);
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num < 0)
			return (printf("argument exceed the limits\n"), -1);
		i++;
	}
	return (0);
}

t_main	*parsing(char **av)
{
	t_main	*result;
	int		total_philos;
	int		i;

	i = 0;
	total_philos = ft_atoi(av[1]);
	result = malloc(sizeof(t_main));
	result->ind_philos = malloc(sizeof(t_ind_philo) * total_philos);
	result->shared = malloc(sizeof(t_shared_info));
	initialize_shared_info(result->shared, total_philos);
	while (i < total_philos)
	{
		result->ind_philos[i].shared_info = result->shared;
		initialize_indiv_info(&result->ind_philos[i], i, av);
		i++;
	}
	return (result);
}

int	initialize_shared_info(t_shared_info *shared, int size)
{
	int	i;

	i = -1;
	shared->dead = 0;
	pthread_mutex_init(&shared->death, NULL);
	shared->forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!shared->forks)
		return (printf("malloc failed\n"), -1);
	shared->time_ate_mutex = malloc(sizeof(pthread_mutex_t) * size);
	if (!shared->time_ate_mutex)
		return (printf("malloc failed\n"), -1);
	shared->time_ate = malloc(sizeof(long long int) * size);
	if (!shared->time_ate)
		return (printf("malloc failed\n"), -1);
	pthread_mutex_init(&shared->to_write, NULL);
	pthread_mutex_init(&shared->mutex_full, NULL);
	shared->full = 0;
	while (++i < size)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		pthread_mutex_init(&shared->time_ate_mutex[i], NULL);
		shared->time_ate[i] = 0;
	}
	return (0);
}

int	initialize_indiv_info(t_ind_philo *philos, int i, char **av)
{
	long long int	sum;

	philos->start_time = 0;
	philos->total_philos = ft_atoi(av[1]);
	philos->t_to_die = ft_atoi(av[2]);
	philos->t_to_eat = ft_atoi(av[3]);
	philos->t_to_sleep = ft_atoi(av[4]);
	sum = (philos->t_to_die - philos->t_to_eat - philos->t_to_sleep);
	philos->t_to_think = sum / 2;
	philos->num_times_ate = 0;
	if (av[5])
		philos->t_each_eat = ft_atoi(av[5]);
	else
		philos->t_each_eat = -1;
	philos->philo_id = i;
	philos->first_fork = (i + 1 - i % 2) % philos->total_philos;
	philos->second_fork = (i + i % 2) % philos->total_philos;
	philos->thread_id = -1;
	return (0);
}
