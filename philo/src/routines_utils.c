/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:47:34 by shabibol          #+#    #+#             */
/*   Updated: 2022/10/04 21:47:35 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_ind_philo *philo, int first, int second)
{
	long long int	ref;

	ref = ft_gettimeofday();
	while (ft_gettimeofday() < (ref + philo->t_to_eat))
	{
		if (ft_read_death(philo->shared_info) == 1)
		{
			pthread_mutex_unlock(&philo->shared_info->forks[second]);
			pthread_mutex_unlock(&philo->shared_info->forks[first]);
			return (1);
		}
		usleep(500);
	}
	return (0);
}

int	mock_up_routine(t_ind_philo *philo)
{
	int				first;
	long long int	ref;

	ref = 0;
	first = philo->first_fork;
	pthread_mutex_lock(&philo->shared_info->forks[first]);
	pthread_mutex_lock(&philo->shared_info->to_write);
	printf("%lld %d has taken a fork\n", \
	ft_gettimeofday() - philo[0].start_time, philo[0].philo_id + 1);
	pthread_mutex_unlock(&philo->shared_info->to_write);
	ref = ft_gettimeofday();
	while (ft_gettimeofday() < (ref + philo->t_to_die))
		usleep(500);
	printf("%lld %d died\n", ft_gettimeofday() - philo->start_time, 1);
	return (0);
}

int	ft_destroy_free(t_main	*all_philos)
{
	pthread_mutex_destroy(all_philos->shared->forks);
	pthread_mutex_destroy(all_philos->shared->time_ate_mutex);
	pthread_mutex_destroy(&all_philos->shared->to_write);
	pthread_mutex_destroy(&all_philos->shared->death);
	pthread_mutex_destroy(&all_philos->shared->mutex_full);
	free(all_philos->shared->forks);
	free(all_philos->shared->time_ate_mutex);
	free(all_philos->shared->time_ate);
	free(all_philos->ind_philos);
	free(all_philos->shared);
	free(all_philos);
	return (0);
}
