/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:25:15 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/15 16:00:10 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	time_last_meal(t_ph *s_ph)
{
	struct timeval	last;

	gettimeofday(&last, NULL);
	s_ph->last = (last.tv_sec * 1000) + (last.tv_usec / 1000);
}

void	init_time_begin(t_ph *s_ph)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	s_ph->ml_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	s_ph->last = s_ph->ml_start;
}
