/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:25:15 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/08 17:18:36 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_between_meal(t_ph *s_ph)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	s_ph->current_m = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	//printf("%ld\n", s_ph->time->ml_start);
	return ((s_ph->current_m - s_ph->first_o_pr_m) * 1000); //return (s_ph->first_o_pr_m - s_ph->current_m);
}

void	time_last_meal(t_ph *s_ph)
{
	struct timeval	last;

	gettimeofday(&last, NULL);
	s_ph->first_o_pr_m = (last.tv_sec * 1000) + (last.tv_usec / 1000);
	//printf("%ld\n", s_ph->first_o_pr_m);
}

void	init_time_begin(t_ph *s_ph)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	s_ph->ml_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	//printf("\n\n%ld\n\n", s_ph->time->ml_start);
}
