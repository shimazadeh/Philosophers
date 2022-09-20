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


int	main(int ac, char **av)
{
	t_struct philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (printf("invalid number of arguments\n", -1));
	if (check_parsing(av, philo) < 0)
		return (-1);

}
