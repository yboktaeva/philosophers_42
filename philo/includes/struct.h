/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:50:07 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/15 14:01:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"
# include <pthread.h>
# include <stdint.h>

# define DIED "died\n"

typedef struct s_philo
{
	pthread_mutex_t	first;
	pthread_mutex_t	*second;
	struct s_data	*data;
	pthread_t		th;
	uint64_t		last_eat;
	int				id;
	int				n_meals;
	int				fin;
}			t_philo;

typedef struct s_data
{
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	eating;
	pthread_mutex_t	finish;
	uint64_t		start;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	t_philo			*philo;
	int				nbr;
	int				n_must_eat;
	int				stop;
	int				all_eat;
}			t_data;

#endif
