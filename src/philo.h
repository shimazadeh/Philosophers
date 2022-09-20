#ifndef _PHILO_H
# define _PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_list
{
	p_thread_t		*thread;
	int				philo_id;
	struct s_list	*next;
}				t_list;

typedef struct t_struct
{
	int			number_philos;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			t_each_eat;

	int			*forks;
	int			*philos;
//	s_list		p_threads;
}				s_struct;

#endif
