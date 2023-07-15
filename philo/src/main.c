/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:06:56 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/07/14 18:38:26 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	one_philo(t_philo *philo)
{
	philo->data->start = curr_time();
	pthread_mutex_lock(&philo->first);
	my_printf(philo, "has taken a fork\n");
	my_usleep(philo->data->t_die + 1);
	pthread_mutex_unlock(&philo->first);
	my_printf(philo, "died\n");
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 1;
	while (i < ac)
	{
		if ((ac != 5 && ac != 6) || parse_args(&av[i]))
		{
			msg("error : Invalid arguments\n");
			return (1);
		}
		i++;
	}
	if (check_init(&data, ac, av) != 0)
		return (1);
	if (data.nbr == 1)
		one_philo(data.philo);
	else
		threading(&data);
	free_all(&data);
	return (0);
}
