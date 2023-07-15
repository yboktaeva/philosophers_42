/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:08:22 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/07/15 13:13:24 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	init_data(t_data *data, int ac, char **av);
static int	init_philo(t_data *data);
int			check_init(t_data *data, int ac, char **av);

static int	init_data(t_data *data, int ac, char **av)
{
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->finish, NULL);
	data->all_eat = 0;
	data->stop = 0;
	data->nbr = ft_atoi(av[1]);
	data->t_die = (uint64_t)ft_atoi(av[2]);
	data->t_eat = (uint64_t)ft_atoi(av[3]);
	data->t_sleep = (uint64_t)ft_atoi(av[4]);
	if (ac == 6)
		data->n_must_eat = ft_atoi(av[5]);
	else
		data->n_must_eat = -1;
	if (data->nbr <= 0 || data->t_die <= 0 || data->t_eat <= 0 \
			|| data->t_sleep <= 0 || data->n_must_eat == 0)
		return (1);
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start = curr_time();
	data->philo = malloc(sizeof(struct s_philo) * data->nbr);
	if (!data->philo)
		return (-1);
	while (i < data->nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].n_meals = 0;
		data->philo[i].last_eat = curr_time();
		data->philo[i].fin = 0;
		if (pthread_mutex_init(&data->philo[i].first, NULL) != 0)
			return (-1);
		if (i == data->nbr - 1)
			data->philo[i].second = &data->philo[0].first;
		else
			data->philo[i].second = &data->philo[i + 1].first;
		i++;
	}
	return (0);
}

int	check_init(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av) != 0)
	{
		msg("error : Invalid arguments\n");
		return (1);
	}
	if (init_philo(data) != 0)
	{
		free_all(data);
		return (1);
	}
	return (0);
}
