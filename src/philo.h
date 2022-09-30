#ifndef _PHILO_H
# define _PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_shared_info
{
	pthread_mutex_t				*forks;
	long long int				*time_ate;
	pthread_mutex_t				*time_ate_mutex;
	pthread_mutex_t				to_write;
	int							dead;
	pthread_mutex_t				death;
	int							full;
	pthread_mutex_t				mutex_full;
}				t_shared_info;

typedef struct s_ind_philo
{
	t_shared_info				*shared_info;

	int							total_philos;
	long long int				t_to_die;
	long long int				t_to_eat;
	long long int				t_to_sleep;
	long long int				t_to_think;
	int							t_each_eat;
	int							num_times_ate;

	long long int				start_time;
	int							philo_id;
	int							right_handed;
	int							first_fork;
	int							second_fork;
	pthread_t					thread_id;


}					t_ind_philo;

typedef struct s_main
{
	t_ind_philo					*ind_philos;
	t_shared_info				*shared;
}				t_main;

int		initialize_indiv_info(t_ind_philo *philos, int i, int size, char **av);
int		initialize_shared_info(t_shared_info *shared, int size);
int 	ft_create_threads(t_ind_philo *all_philos, int total_philos);
void	*execute(void *philo);
t_main	*parsing(char **av);
int		ft_initialize_time(t_main *philos, int total_philos);

int		argument_check(char **av, int ac);
int 	ft_is_num(char *str);
int		ft_atoi(const char *str);
int		ft_read_death(int dead, pthread_mutex_t death);

int		check_if_program_ends(t_ind_philo philo);

void	display_content(t_ind_philo philo);

#endif
