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


int	execute(t_ind_philo ind_philo)
{
	int	right;
	int	left;

	right = ind_philo->right_fork;
	left = ind_philo->left_fork;
	if (ind_philo->right_handed == 1)//philo is right handed it starts with right fork
	{
		if (pthread_mutex_lock(ind_philo->shared_info->forks[right]) == 0)
			printf("%ld: philo %d has taken a fork\n", gettimeofday(), ind_philo->philo_id);
		if (pthread_mutex_lock(ind_philo->shared_info->forks[left]) == 0)
			printf("%ld: philo %d has taken a fork\n", gettimeofday(), ind_philo->philo_id);
	}
	else
	{
		if (pthread_mutex_lock(ind_philo->shared_info->forks[left]) == 0)
			printf("%ld: philo %d has taken a fork\n", gettimeofday(), ind_philo->philo_id);
		if (pthread_mutex_lock(ind_philo->shared_info->forks[right]) == 0)
			printf("%ld: philo %d has taken a fork\n", gettimeofday(), ind_philo->philo_id);
	}
	printf("%ld: philo %d is eating\n", gettimeofday(), ind_philo->philo_id);
	usleep(ind_philo->t_to_eat);
	pthread_mutex_unlock(ind_philo->shared_info->forks[left]);
	pthread_mutex_unlock(ind_philo->shared_info->forks[right]);
	ind_philo->num_times_ate++;
	ind_philo->shared_info->time_ate[ind_philo->philo_id] = gettimeofday();

	printf("%ld: philo %d is sleeping\n", gettimeofday(), ind_philo->philo_id);
	usleep(ind_philo->t_to_sleep);
	printf("%ld: philo %d is thinking\n", gettimeofday(), ind_philo->philo_id);

	return (0);
}

int ft_create_threads(t_ind_philo all_philos)
{
	int i;

	i = 0;
	while(all_philos[i])
	{
		if (pthread_create(all_philos[i]->pthread_id, NULL, &execute, all_philos[i]) != 0)
			return (printf("error creating threads\n"), -1);
		i++;
	}
	return (0);
}

int	check_if_dead(t_shared_philo shared_info)
{
	while(1)
	{

	}
}

int	main(int ac, char **av)
{
	t_main	philos;
	int		i;

	i = 0;
	philo = NULL;
	if (argument_check(av, ac) < 0)
		return (-1);
	philos = parsing(av);
	if (ft_create_threads(philos->ind_philos) < 0)
		return (-1);
	while(philos->ind_philos[i])
	{
		pthread_join(philos->ind_philos[i]->thread_id, NULL);
		i++;
	}

	return (0);
}
