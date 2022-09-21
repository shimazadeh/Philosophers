#include "philo.h"

int ft_is_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (c >= '0' && c <= '9')
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
		return (printf("invalid number of arguments\n", -1));
	while (av[i])
	{
		if (ft_is_num(av[i]) < 0)
			return (printf("invalid characters in the argument\n"), -1);
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num < 0)
			return (printf("argument exceed the limits\n"), -1);
		i++;
	}
	return (0);
}

t_main	parsing(char **av)
{
	t_main	result;
	int		total_philos;

	total_philos = ft_atoi(av[1]);

	result = malloc(sizeof(s_main));
	result->ind_philos = malloc(sizeof(s_ind_philos) * total_philos);
	result->shared = malloc(sizeof(s_shared_info));

	if (initialize_shared_info(result->shared, total_philos) < 0)
		return (NULL);
	if (initialize_indiv_info(result->ind_philos, total_philos, av) < 0)
		return (NULL);
	return (result);
}

int	initialize_shared_info(t_shared_info shared, int size)
{
	int i;

	i = 0;
	shared->forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!shared->forks)
		return (printf("malloc failed\n"), -1);
	shared->time_ate_mutex = malloc(sizeof(pthread_mutex_t) * size);
	if (!shared->time_ate_mutex)
		return (printf("malloc failed\n"), -1);
	shared->time_ate = malloc(sizeof(int) * size);
	if (!shared->time_ate)
		return (printf("malloc failed\n"), -1);
	while (i <= size)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
			return (printf("error initializing the mutex\n", -1));
		if (pthread_mutex_init(&shared->time_ate_mutex[i], NULL) != 0)
			return (printf("error initializing the mutex\n", -1));
		shared->time_ate[i] = 0;
		i++;
	}
	return (0);
}

int	initialize_indiv_info(t_ind_philo *philos, int size, char **av)
{
	int i;

	i = 0;
	while(i <= size)
	{
		philos[i]->t_to_die = ft_atoi(av[2]);
		philos[i]->t_to_eat = ft_atoi(av[3]);
		philos[i]->t_to_sleep = ft_atoi(av[4]);
		philos[i]->num_times_ate = 0;
		if (av[5])
			philos[i]->t_each_eat = ft_atoi(av[5]);
		else
			philos[i]->t_each_eat = -1;

		philos[i]->philo_id = i;
		if (i % 2)
			philos[i]->right_handed = 0;
		else
			philos[i]->right_handed = 1;
		if (i == 0)
			philos[i]->right_fork = size -1;
		else
			philos[i]->right_fork = i - 1;//write it better
		philos[i]->left_fork = i;
		philos[i]->thread_id = -1;
		i++;
	}
	return (0);
}
