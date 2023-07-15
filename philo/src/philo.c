/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:23:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/15 13:25:48 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void	*monitoring(void *arg);
void	*exec_philo(void *arg);
void	threading(t_data *data);

void	*monitoring(void *arg)
{
	t_philo		*philo;
	uint64_t	t;

	philo = (t_philo *)arg;
	t = (2 * philo->data->t_sleep);
	my_usleep(philo->data->t_die + 1);
	pthread_mutex_lock(&philo->data->eating);
	pthread_mutex_lock(&philo->data->finish);
	if ((!is_dead(philo, 0) && curr_time()
			- philo->last_eat > philo->data->t_die)
		|| philo->data->t_sleep > philo->data->t_die || t == philo->data->t_eat)
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_unlock(&philo->data->finish);
		my_printf(philo, DIED);
		is_dead(philo, 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_unlock(&philo->data->finish);
	}
	return (NULL);
}

void	*exec_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(philo->data->t_eat / 10);
	while (!is_dead(philo, 0))
	{
		eat_sleep_think(philo);
		if (philo->n_meals == philo->data->n_must_eat)
		{
			pthread_mutex_lock(&philo->data->finish);
			philo->fin = 1;
			philo->data->all_eat++;
			if (philo->data->all_eat == philo->data->nbr)
			{
				pthread_mutex_unlock(&philo->data->finish);
				is_dead(philo, 2);
			}
			else
				pthread_mutex_unlock(&philo->data->finish);
			return (NULL);
		}
	}
	return (NULL);
}

void	threading(t_data *data)
{
	int			i;
	pthread_t	m;

	i = 0;
	if (pthread_create(&m, NULL, &monitoring, (void *)data->philo) != 0)
		msg("error : Failed to create thread\n");
	while (i < data->nbr)
	{
		if (pthread_create(&data->philo[i].th, NULL, &exec_philo,
				&data->philo[i]) != 0)
			msg("error : Failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < data->nbr)
	{
		if (pthread_join(data->philo[i].th, NULL) != 0)
			msg("error : Failed to join thread\n");
		i++;
	}
	pthread_detach(m);
}
