/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:36:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/15 13:20:33 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <pthread.h>
#include <stdlib.h>

void	free_all(t_data *data);

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr)
	{
		pthread_mutex_destroy(&data->philo[i].first);
		i++;
	}
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->finish);
}
