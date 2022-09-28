#include "philo.h"

int ft_is_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
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

	total_philos = ft_atoi(av[1]);
	result = NULL;
	result = malloc(sizeof(t_main));
	result->ind_philos = malloc(sizeof(t_ind_philo) * total_philos);
	result->shared = malloc(sizeof(t_shared_info));

	if (initialize_shared_info(result->shared, total_philos) < 0)
		dprintf(2, "initialization error\n");
	i = 0;
	while(i < total_philos)
	{
		result->ind_philos[i].shared_info = result->shared;
		if (initialize_indiv_info(&result->ind_philos[i], i, total_philos, av) < 0)
			dprintf(2, "initialization error\n");
		// display_content(result->ind_philos[i]);
		i++;
	}
	return (result);
}

int	initialize_shared_info(t_shared_info *shared, int size)
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
	if (pthread_mutex_init(&shared->to_write, NULL) != 0)
		return (printf("erroro initializing mutex\n"), -1);
	while (i < size)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
			return (printf("error initializing the mutex\n"), -1);
		if (pthread_mutex_init(&shared->time_ate_mutex[i], NULL) != 0)
			return (printf("error initializing the mutex\n") -1);
		shared->time_ate[i] = 0;
		i++;
	}
	return (0);
}

int	initialize_indiv_info(t_ind_philo *philos, int i, int size, char **av)
{
	philos->total_philos = ft_atoi(av[1]);
	philos->t_to_die = ft_atoi(av[2]);
	philos->t_to_eat = ft_atoi(av[3]);
	philos->t_to_sleep = ft_atoi(av[4]);
	philos->num_times_ate = 0;
	if (av[5])
		philos->t_each_eat = ft_atoi(av[5]);
	else
		philos->t_each_eat = -1;

	philos->philo_id = i;
	if (i % 2)
		philos->right_handed = 0;
	else
		philos->right_handed = 1;
	if (i == 0)
		philos->right_fork = size -1;
	else
		philos->right_fork = i - 1;//write it better
	philos->left_fork = i;
	philos->thread_id = -1;
	// display_content(*philos);
	return (0);
}

void	display_content(t_ind_philo philo)
{
	printf("philo id : %d\n", philo.philo_id);
	printf("right hand: %d\n", philo.right_handed);
	printf("right fork id: %d\n", philo.right_fork);
	printf("left fork id: %d\n", philo.left_fork);
	printf("time to eat: %lld\n", philo.t_to_eat);
	printf("time to eat: %lld\n", philo.t_to_die);
	printf("time to eat: %lld\n", philo.t_to_sleep);
	printf("---------------------------------------\n");
}
