#include "philo.h"

int ft_is_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (c >= '0' && c <= '9'))
			i++;
		else
			return (-1);
	}
	return (0);
}

int	initialize_threads(t_list pthreads, int size)
{
	int i;

	i = 1;
	while(size)
	{
		pthreads = malloc(sizeof(t_list));
		if (pthread_create(pthreads->thread, NULL, &execution, ) != 0)
		{
			printf("thread creation failure\n");
			return (-1);
		}
		pthreads->philo_id = i;
		i++;
		pthreads->next = NULL;
		pthreads = pthreads->next;
	}
}

int	initialize_forks(int *forks)
{
	int i;

	i = 0;
	while(forks[i])
	{
		forks[i] = ++i;
	}
	return (0);
}

int parsing(char **av, t_struct philo)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_is_num(av[i]) < 0)
			return (printf("invalid characters in the argument\n"), -1);
		i++;
	}
	philo->number_philos = ft_atoi(av[1]);
	philo->t_to_die = ft_atoi(av[2]);
	philo->t_to_eat = ft_atoi(av[3]);
	philo->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->t_each_eat = ft_atoi(av[5]);
	else
		philo->t_each_eat = -1;

	philo->forks = malloc(sizeof(int) * philo->number_philos);
	initialize_forks(philo->forks);

	philo->p_threads = NULL;
	initialize_threads(philo->pthreads, philo->number_philos);
	return (0);
}
