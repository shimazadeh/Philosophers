/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:23:51 by shabibol          #+#    #+#             */
/*   Updated: 2022/10/04 19:23:52 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_read_death(t_shared_info *shared)
{
	int	res;

	pthread_mutex_lock(&shared->death);
	if (shared->dead == 1)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&shared->death);
	return (res);
}

int	check_if_program_ends(t_ind_philo philo)
{
	if (philo.num_times_ate == philo.t_each_eat)
	{
		pthread_mutex_lock(&philo.shared_info->death);
		pthread_mutex_lock(&philo.shared_info->mutex_full);
		philo.shared_info->full++;
		if (philo.shared_info->full == philo.total_philos)
			philo.shared_info->dead = 1;
		pthread_mutex_unlock(&philo.shared_info->death);
		pthread_mutex_unlock(&philo.shared_info->mutex_full);
	}
	return (0);
}

int	check_if_dead(t_ind_philo *philo, t_shared_info *shared)
{
	int				i;
	long long int	min;
	int				min_id;

	while (1)
	{
		i = -1;
		while (++i < philo->total_philos)
		{
			pthread_mutex_lock(&shared->time_ate_mutex[i]);
			if (!i || shared->time_ate[i] < min)
			{
				min = shared->time_ate[i];
				min_id = i;
			}
			pthread_mutex_unlock(&shared->time_ate_mutex[i]);
		}
		usleep(500);
		while (ft_gettimeofday() < (min + philo->t_to_die))
			usleep(500);
		usleep(500);
		if (check_death(shared, philo, min_id, min) == 1)
			return (1);
	}
	return (0);
}

int	check_death(t_shared_info *shared, t_ind_philo *philo, \
int min_id, long long int min)
{
	pthread_mutex_lock(&shared->time_ate_mutex[min_id]);
	if (shared->time_ate[min_id] == min)
	{
		pthread_mutex_lock(&shared->death);
		shared->dead = 1;
		pthread_mutex_unlock(&shared->death);
		printf("%lld %d died\n", \
		ft_gettimeofday() - philo->start_time, min_id + 1);
		pthread_mutex_unlock(&shared->time_ate_mutex[min_id]);
		return (1);
	}
	pthread_mutex_unlock(&shared->time_ate_mutex[min_id]);
	return (0);
}
