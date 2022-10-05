/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:27:28 by shabibol          #+#    #+#             */
/*   Updated: 2022/09/20 12:27:29 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettimeofday(void)
{
	struct timeval	time;
	long long int	res;

	res = 0;
	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + (time.tv_usec / 1000);
	return (res);
}

int	ft_initialize_time(t_main *philos, int total_philos)
{
	long long int	time;
	int				i;

	i = 0;
	time = ft_gettimeofday();
	while (i < total_philos)
	{
		philos->ind_philos[i].start_time = time;
		philos->shared->time_ate[i] = time;
		i++;
	}
	return (0);
}

void	*execute(void *philo)
{
	int				first;
	int				second;
	t_ind_philo		*ind_philo;

	ind_philo = (t_ind_philo *)philo;
	first = ind_philo->first_fork;
	second = ind_philo->second_fork;
	while (1)
	{
		if (take_first_fork(ind_philo, first) == 1)
			return (NULL);
		if (take_second_fork(ind_philo, second, first) == 1)
			return (NULL);
		if (eating(ind_philo, first, second) == 1)
			return (NULL);
		check_if_program_ends(ind_philo[0]);
		if (sleeping(ind_philo) == 1)
			return (NULL);
		if (thinking(ind_philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	ft_create_threads(t_ind_philo *all_philos, int total_philos)
{
	int				i;

	i = 0;
	while (i < total_philos)
	{
		if (pthread_create(&all_philos[i].thread_id, NULL, &execute, \
		(void *)&all_philos[i]) != 0)
		{
			pthread_mutex_lock(&all_philos->shared_info->end_mutex);
			pthread_mutex_lock(&all_philos->shared_info->to_write);
			all_philos->shared_info->end = 1;
			printf("error creating threads\n");
			pthread_mutex_unlock(&all_philos->shared_info->to_write);
			pthread_mutex_unlock(&all_philos->shared_info->end_mutex);
			break ;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main	*philos;
	int		i;

	i = 0;
	philos = NULL;
	if (argument_check(av, ac) < 0)
		return (-1);
	philos = parsing(av);
	ft_initialize_time(philos, philos->ind_philos[0].total_philos);
	if (philos->ind_philos[0].total_philos == 1)
		mock_up_routine(philos->ind_philos);
	else
	{
		ft_create_threads(philos->ind_philos, ft_atoi(av[1]));
		check_if_dead(philos->ind_philos, philos->shared);
		while (i < ft_atoi(av[1]))
		{
			pthread_join(philos->ind_philos[i].thread_id, NULL);
			i++;
		}
	}
	ft_destroy_free(philos);
	return (0);
}
