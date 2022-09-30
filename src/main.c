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

long long ft_gettimeofday(void)
{
	struct timeval time;
	long long int	res;

	res = 0;
	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + (time.tv_usec / 1000);
	return (res);
}

void	*execute(void *philo)
{
	int				first;
	int				second;
	t_ind_philo		*ind_philo;
	long long int	ref;

	ref = 0;
	ind_philo = (t_ind_philo *)philo;
	first = ind_philo->first_fork;
	second = ind_philo->second_fork;
	while (1)
	{
		pthread_mutex_lock(&ind_philo[0].shared_info->forks[first]);
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
		{
			pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
			return (NULL);
		}
		printf("%lld %d has taken a fork\n", ft_gettimeofday() - ind_philo[0].start_time, ind_philo->philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);


		pthread_mutex_lock(&ind_philo[0].shared_info->forks[second]);
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
		{
			pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
			return (NULL);
		}
		printf("%lld %d has taken a fork\n", ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);

		ind_philo[0].shared_info->time_ate[ind_philo[0].philo_id] = ft_gettimeofday();
		//eating
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
		{
			pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
			pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
			return (NULL);
		}
		printf("%lld %d is eating\n", ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
		ref = ft_gettimeofday();
		while(ft_gettimeofday() < (ref + ind_philo[0].t_to_eat))
		{
			if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
			{
				pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
				pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
				return (NULL);
			}
			usleep(500);
		}
		pthread_mutex_unlock(&ind_philo->shared_info->forks[second]);
		pthread_mutex_unlock(&ind_philo->shared_info->forks[first]);
		ind_philo[0].num_times_ate++;

		check_if_program_ends(ind_philo[0]);

		//sleeping
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
		{
			pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			return (NULL);
		}
		printf("%lld %d is sleeping\n", ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
		ref = ft_gettimeofday();
		while(ft_gettimeofday() < (ref + ind_philo[0].t_to_sleep))
		{
			if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
				return (NULL);
			usleep(500);
		}

		//thinking
		pthread_mutex_lock(&ind_philo[0].shared_info->to_write);
		if (ind_philo[0].shared_info->dead == 1)
		{
			pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
			return (NULL);
		}
		printf("%lld %d is thinking\n", ft_gettimeofday() - ind_philo[0].start_time, ind_philo[0].philo_id);
		pthread_mutex_unlock(&ind_philo[0].shared_info->to_write);
		ref = ft_gettimeofday();
		while(ft_gettimeofday() < (ref + ind_philo[0].t_to_think))
		{
			if (ft_read_death(ind_philo[0].shared_info->dead, ind_philo[0].shared_info->death) == 1)
				return (NULL);
			usleep(500);
		}
	}
	return (NULL);
}

int	ft_read_death(int dead, pthread_mutex_t death)
{
	int res;

	pthread_mutex_lock(&death);
	if (dead == 1)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&death);
	return (res);
}
int ft_create_threads(t_ind_philo *all_philos, int total_philos)
{
	int				i;
	long long int	time;

	time = ft_gettimeofday();
	i = 0;
	while(i < total_philos)
	{
		if (pthread_create(&all_philos[i].thread_id, NULL, &execute, (void *)&all_philos[i]) != 0)
			return (printf("error creating threads\n"), -1);

		i++;
	}
	return (0);
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
	int	i;
	long long int	min;
	int	min_id;

	while(1)
	{
		i = 0;
		while (i < philo->total_philos)
		{
			// printf("shared time is %lld\n", shared->time_ate[i]);
			if (!i || shared->time_ate[i] < min)
			{
				min = shared->time_ate[i];
				min_id = i;
			}
			i++;
		}
		// printf("min is %lld\n", min);
		usleep(500);
		while (ft_gettimeofday() < (min + philo->t_to_die))
		{
			usleep(500);
		}
		usleep(500);
		if (shared->time_ate[min_id] == min)
		{
			pthread_mutex_lock(&shared->death);
			shared->dead = 1;
			pthread_mutex_unlock(&shared->death);
			printf("%lld %d died\n", ft_gettimeofday() - philo->start_time, min_id);
			return (1);
		}
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
	if (ft_create_threads(philos->ind_philos, ft_atoi(av[1])) < 0)
		return (-1);
	check_if_dead(philos->ind_philos, philos->shared);
	while(i < ft_atoi(av[1]))
	{
		pthread_join(philos->ind_philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}

int	ft_initialize_time(t_main *philos, int total_philos)
{
	long long int	time;
	int				i;

	i = 0;
	time = ft_gettimeofday();
	while(i < total_philos)
	{
		philos->ind_philos[i].start_time = time;
		philos->shared->time_ate[i] = time;
		i++;
	}
	return (0);
}
