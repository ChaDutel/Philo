/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/03 17:30:02 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				n;
	int				res;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = n * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * n);
}

void	init(char **argv, t_ph *s_ph)
{
	s_ph->nb_philo = ft_atoi(argv[1]);
	s_ph->time_die = ft_atoi(argv[2]) * 100;
	s_ph->time_eat = ft_atoi(argv[3]) * 100;
	s_ph->time_sleep = ft_atoi(argv[4]) * 100;
}
