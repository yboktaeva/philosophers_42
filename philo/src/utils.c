/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:56:12 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/07/14 19:41:55 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

static int	ft_strcmp(char *s1, char *s2);
uint64_t	curr_time(void);
void		my_usleep(uint64_t ms);
void		my_printf(t_philo *philo, char *str);
int			is_dead(t_philo *philo, int flag);

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((*(char *)s1) - *(char *)s2);
}

uint64_t	curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(uint64_t ms)
{
	uint64_t	now;

	now = curr_time();
	while (curr_time() - now < ms)
		usleep(ms / 10);
}

void	my_printf(t_philo *philo, char *str)
{
	uint64_t	time;

	time = curr_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->write);
	if (!is_dead(philo, 0) && ft_strcmp(DIED, str) == 0)
	{
		printf("%lu %d %s", time, philo->id, str);
		is_dead(philo, 1);
	}
	if (!is_dead(philo, 0))
		printf("%lu %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

int	is_dead(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->data->dead);
	if (flag)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->data->dead);
	return (0);
}
