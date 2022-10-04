/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:23:45 by shabibol          #+#    #+#             */
/*   Updated: 2022/10/04 19:23:46 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_first_fork(t_ind_philo	*ind_philo, int first)
{
	pthread_mutex_lock(&ind_philo->shared_info->forks[first]);
	pthread_mutex_lock(&ind_philo->shared_info->to_write);
	if (ft_read_death(ind_philo->shared_info) == 1)
	{
		pthread_mutex_unlock(&ind_philo->shared_info->to_write);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
	ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id + 1);
	pthread_mutex_unlock(&ind_philo->shared_info->to_write);
	return (0);
}

int	take_second_fork(t_ind_philo *ind_philo, int second)
{
	pthread_mutex_lock(&ind_philo->shared_info->forks[second]);
	pthread_mutex_lock(&ind_philo->shared_info->to_write);
	if (ft_read_death(ind_philo->shared_info) == 1)
	{
		pthread_mutex_unlock(&ind_philo->shared_info->to_write);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
	ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id + 1);
	pthread_mutex_unlock(&ind_philo->shared_info->to_write);
	return (0);
}

int	eating(t_ind_philo *ind_philo, int first, int second)
{
	long long int	ref;
	int				id;

	id = ind_philo->philo_id;
	ref = 0;
	pthread_mutex_lock(&ind_philo->shared_info->time_ate_mutex[id]);
	ind_philo->shared_info->time_ate[id] = ft_gettimeofday();
	pthread_mutex_unlock(&ind_philo->shared_info->time_ate_mutex[id]);
	pthread_mutex_lock(&ind_philo->shared_info->to_write);
	if (ft_read_death(ind_philo->shared_info) == 1)
	{
		pthread_mutex_unlock(&ind_philo->shared_info->to_write);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
		return (1);
	}
	printf("%lld %d is eating\n", \
	ft_gettimeofday() - ind_philo[0].start_time, id + 1);
	pthread_mutex_unlock(&ind_philo->shared_info->to_write);
	if (ft_usleep(ind_philo, first, second) == 1)
		return (1);
	ind_philo->num_times_ate++;
	pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
	pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
	return (0);
}

int	sleeping(t_ind_philo *ind_philo)
{
	long long int	ref;

	ref = 0;
	pthread_mutex_lock(&ind_philo->shared_info->to_write);
	if (ft_read_death(ind_philo->shared_info) == 1)
	{
		pthread_mutex_unlock(&ind_philo->shared_info->to_write);
		return (1);
	}
	printf("%lld %d is sleeping\n", \
	ft_gettimeofday() - ind_philo[0].start_time, ind_philo->philo_id + 1);
	pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
	ref = ft_gettimeofday();
	while (ft_gettimeofday() < (ref + ind_philo->t_to_sleep))
	{
		if (ft_read_death(ind_philo->shared_info) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	thinking(t_ind_philo *ind_philo)
{
	long long int	ref;

	ref = 0;
	pthread_mutex_lock(&ind_philo->shared_info->to_write);
	if (ft_read_death(ind_philo->shared_info) == 1)
	{
		pthread_mutex_unlock(&ind_philo->shared_info->to_write);
		return (1);
	}
	printf("%lld %d is thinking\n", \
	ft_gettimeofday() - ind_philo->start_time, ind_philo->philo_id + 1);
	pthread_mutex_unlock(&ind_philo->shared_info->to_write);
	ref = ft_gettimeofday();
	while (ft_gettimeofday() < (ref + ind_philo->t_to_think))
	{
		if (ft_read_death(ind_philo->shared_info) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}
