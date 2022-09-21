#ifndef _PHILO_H
# define _PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct t_shared_info
{
	pthread_mutex_t				*forks;
	int							*time_ate;

}				s_shared_info;

typedef struct t_ind_philo
{
	t_shared_philo				*shared_info;

	long long int				t_to_die;
	long long int				t_to_eat;
	long long int				t_to_sleep;
	int							t_each_eat;
	int							num_times_ate;

	int							philo_id;
	int							right_handed;
	int							right_fork;
	int							left_fork;
	pthread_t					thread_id;


}					s_ind_philo;

typedef struct t_main
{
	t_ind_info					*ind_philos;
	t_shared_info				shared;

}				s_main;





#endif
