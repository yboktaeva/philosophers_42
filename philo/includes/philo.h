/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:06:45 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/15 14:41:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <pthread.h>
# include <sys/time.h>

/*INIT*/
int			check_init(t_data *data, int ac, char **av);
/*PHILO*/
void		eat_sleep_think(t_philo *philo);
void		*exec_philo(void *arg);
void		*monitoring(void *arg);
void		threading(t_data *data);
void		my_printf(t_philo *philo, char *str);
/*LIB*/
int			is_digit(int c);
int			ft_strlen(char *str);
int			ft_atoi(char *str);
void		msg(char *str);
/*UTILS*/
int			parse_args(char **str);
int			is_dead(t_philo *philo, int flag);
void		free_all(t_data *data);
void		my_usleep(uint64_t ms);
uint64_t	curr_time(void);
#endif
