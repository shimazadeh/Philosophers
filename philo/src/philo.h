/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:28:28 by shabibol          #+#    #+#             */
/*   Updated: 2022/10/04 19:28:30 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

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
	int							first_fork;
	int							second_fork;
	pthread_t					thread_id;
}					t_ind_philo;

typedef struct s_main
{
	t_ind_philo					*ind_philos;
	t_shared_info				*shared;
}				t_main;

//routine
int			take_first_fork(t_ind_philo	*ind_philo, int first);
int			take_second_fork(t_ind_philo *ind_philo, int second);
int			eating(t_ind_philo *ind_philo, int first, int second);
int			sleeping(t_ind_philo *ind_philo);
int			thinking(t_ind_philo *ind_philo);
int			ft_usleep(t_ind_philo *philo, int first, int second);
void		*execute(void *philo);

//initializing
int			ft_initialize_time(t_main *philos, int total_philos);
int			initialize_indiv_info(t_ind_philo *philos, int i, char **av);
int			initialize_shared_info(t_shared_info *shared, int size);
int			ft_create_threads(t_ind_philo *all_philos, int total_philos);

//parsing
t_main			*parsing(char **av);
int				argument_check(char **av, int ac);
int				ft_is_num(char *str);
long long int	ft_atoi(const char *str);

//special case for 1 philo

int			mock_up_routine(t_ind_philo *philo);

//check for end/death
int			ft_read_death(t_shared_info *shared);
int			check_if_program_ends(t_ind_philo philo);
int			check_if_dead(t_ind_philo *philo, t_shared_info *shared);
int			check_death(t_shared_info *shared, \
t_ind_philo *philo, int min_id, long long int min);

long long	ft_gettimeofday(void);

int			ft_destroy_free(t_main	*all_philos);

void		display_content(t_ind_philo philo);

#endif
