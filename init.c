/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:26 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/06 18:04:20 by cdutel-l         ###   ########.fr       */
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

void	init_time_begin(t_ph *s_ph)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	s_ph->time->ml_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	printf("\n\n%ld\n\n", s_ph->time->ml_start);
}

int	init_mutexs(t_ph *s_ph)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(s_ph->mutex_write), NULL);
	s_ph->butler->forks = malloc(sizeof(pthread_mutex_t) \
		* s_ph->butler->nb_forks);
	if (!s_ph->butler->forks)
		return (-1);
	while (i < s_ph->butler->nb_forks)
	{
		pthread_mutex_init(&(s_ph->butler->forks[i]), NULL);
		i++;
	}
	return (0);
}

int	init_struc_elms(int argc, char **argv, t_ph *s_ph)
{
	s_ph->nb_philo = ft_atoi(argv[1]);
	s_ph->butler->nb_forks = s_ph->nb_philo - 1;
	s_ph->time_die = ft_atoi(argv[2]) * 100;
	s_ph->time_eat = ft_atoi(argv[3]) * 100;
	s_ph->time_sleep = ft_atoi(argv[4]) * 100;
	s_ph->max_food_to_eat = -1;
	s_ph->id = 1;
	if (argc == 6)
		s_ph->max_food_to_eat = ft_atoi(argv[5]);
	if (init_mutexs(s_ph) == -1)
		return (-1);
	init_time_begin(s_ph);
	return (check_min_values(s_ph));
}
