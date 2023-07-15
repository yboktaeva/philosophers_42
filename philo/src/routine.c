/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:14:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/15 13:26:37 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

static void	lock_forks(t_philo *philo);
void		eat_sleep_think(t_philo *philo);

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->first);
		pthread_mutex_lock(philo->second);
	}
	else
	{
		pthread_mutex_lock(philo->second);
		pthread_mutex_lock(&philo->first);
	}
}

void	eat_sleep_think(t_philo *philo)
{
	lock_forks(philo);
	my_printf(philo, "has taken a fork\n");
	my_printf(philo, "is eating\n");
	my_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = curr_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->data->eating);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->second);
		pthread_mutex_unlock(&philo->first);
	}
	else
	{
		pthread_mutex_unlock(&philo->first);
		pthread_mutex_unlock(philo->second);
	}
	my_printf(philo, "is sleeping\n");
	my_usleep(philo->data->t_sleep);
	my_printf(philo, "is thinking\n");
	my_usleep(philo->data->t_sleep);
}
