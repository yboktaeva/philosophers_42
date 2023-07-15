/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:40:50 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/14 17:29:14 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/struct.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(char *str);
void	msg(char *str);
int		is_digit(int c);
int		parse_args(char **str);
int		ft_atoi(char *str);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	msg(char *str)
{
	write(1, str, ft_strlen(str));
}

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	parse_args(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!is_digit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && ft_strlen(str) <= 11)
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (sign == -1)
		return (nb * sign);
	return (nb);
}
