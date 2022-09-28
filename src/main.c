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

void	*execute(void *philo)
{
	int				right;
	int				left;
	struct timeval	time;
	t_ind_philo		*ind_philo;

	ind_philo = (t_ind_philo *) philo;
	right = ind_philo->right_fork;
	left = ind_philo->left_fork;
	while (1)
	{
		if (ind_philo->right_handed == 1)//philo is right handed it starts with right fork
		{
			if (pthread_mutex_lock(&ind_philo[0].shared_info->forks[right]) == 0)
			{
				pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
				gettimeofday(&time, NULL);
				printf("%ld: philo %d has taken a fork\n", time.tv_usec, ind_philo->philo_id);
				pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			}
			if (pthread_mutex_lock(&ind_philo[0].shared_info->forks[left]) == 0)
			{
				pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
				gettimeofday(&time, NULL);
				printf("%ld: philo %d has taken a fork\n", time.tv_usec, ind_philo[0].philo_id);
				pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			}
		}
		else
		{
			if (pthread_mutex_lock(&ind_philo[0].shared_info->forks[left]) == 0)
			{
				pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
				gettimeofday(&time, NULL);
				printf("%ld: philo %d has taken a fork\n", time.tv_usec, ind_philo[0].philo_id);
				pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			}
			if (pthread_mutex_lock(&ind_philo[0].shared_info->forks[right]) == 0)
			{
				pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
				gettimeofday(&time, NULL);
				printf("%ld: philo %d has taken a fork\n", time.tv_usec, ind_philo[0].philo_id);
				pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			}
		}
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		gettimeofday(&time, NULL);
		printf("%ld: philo %d is eating\n", time.tv_usec, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
		usleep(ind_philo[0].t_to_eat);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[left]);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[right]);

		ind_philo[0].num_times_ate++;
		ind_philo[0].shared_info->time_ate[ind_philo[0].philo_id] = time.tv_usec;

		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		gettimeofday(&time, NULL);
		printf("%ld: philo %d is sleeping\n", time.tv_usec, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
		usleep(ind_philo[0].t_to_sleep);

		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		gettimeofday(&time, NULL);
		printf("%ld: philo %d is thinking\n", time.tv_usec, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);



		if (check_if_program_ends(philo) < 0)
			return (NULL);
	}
	return (NULL);
}

int ft_create_threads(t_ind_philo *all_philos, int total_philos)
{
	int		i;

	i = 0;
	while(i < total_philos)
	{
		// display_content(all_philos[i]);
		if (pthread_create(&all_philos[i].thread_id, NULL, &execute, (void *)&all_philos[i]) != 0)
			return (printf("error creating threads\n"), -1);
		i++;
	}
	return (0);
}

int	check_if_program_ends(t_ind_philo *philo)
{
	int i;

	i = 0;
	if (philo[i].t_each_eat)
	{
		if (philo[i].num_times_ate == philo[i].t_each_eat)
			return (-1);
		else
			return (0);
	}
	return (0);
}

int	check_if_dead(t_ind_philo *philo, t_shared_info *shared)
{
	int	i;
	int	min;
	int	min_id;

	i = 0;
	min = 2147483647;
	min_id = 0;
	while (i < philo->total_philos)
	{
		if (shared->time_ate[i] < min)
		{
			min = shared->time_ate[i];
			min_id = i;
		}
		i++;
	}
	usleep(philo->t_to_die - min);
	if (shared->time_ate[min_id] == min)
		return (1);
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
	if (ft_create_threads(philos->ind_philos, ft_atoi(av[1])) < 0)
		return (-1);
	while (1)
	{
		if (check_if_dead(philos->ind_philos, philos->shared_info) == 1)
			return (1);
	}
	while(i < ft_atoi(av[1]))
	{
		pthread_join(philos->ind_philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
