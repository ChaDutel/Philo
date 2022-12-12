/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:22:40 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/12 20:33:53 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	execute_routine(t_ph *philo)
{
	while (1)
	{
		if (philo->butler->sebastien != 0)
			return ;
		eat(philo);
		if (philo->butler->sebastien != 0)
			return ;
		sleeping(philo);
		if (philo->butler->sebastien != 0)
			return ;
		think(philo);
	}
}

void	execute_routine_with_limit_food(t_ph *philo, int i)
{
	while (i < philo->max_food_to_eat)
	{
		if (philo->butler->sebastien != 0)
			return ;
		eat(philo);
		philo->food += 1;
		if (philo->butler->sebastien != 0)
			return ;
		sleeping(philo);
		if (philo->butler->sebastien != 0)
			return ;
		think(philo);
		i++;
	}
}

void	execute_routine_for_one(t_ph *philo)
{
	print_state(philo, TAKE_F);
	usleep(philo->time_die);
}

void	*routine(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = (t_ph *) phi;
	if (philo->id % 2 == 0)
		usleep(500);
	print_state(philo, JOIN);
	i = 0;
	if (philo->nb_philo == 1)
		execute_routine_for_one(philo);
	else if (philo->max_food_to_eat != -1)
		execute_routine_with_limit_food(philo, i);
	else
		execute_routine(philo);
	return (0);
}

void	*check_dead(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = phi;
	while (1)
	{
		usleep(2000);
		i = 0;
		while (i < philo[0].nb_philo)
		{
			if (time_between_meal(&philo[i]) > philo[i].time_die)
			{
				philo[i].butler->sebastien = 1;
				if (philo[i].food != philo[i].max_food_to_eat)
					print_state(&philo[i], DIE);
				break ;
			}
			i++;
		}
		if (philo[0].butler->sebastien != 0)
			break ;
	}
	return (0);
}
