/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/10 18:07:24 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	execute_routine(t_ph *philo)
{
	while (1)
	{
		if (philo->butler->sebastien != 0)
		{
			philo->butler->dead_sig += 1;
			break ;
		}
		eat(philo);
		//philo->check_first_meal = 1;
		if (philo->stop != 0) //if (philo->butler->sebastien != 0)
			return ;
		sleeping(philo);
		think(philo);
	}
}

void	execute_routine_with_limit_food(t_ph *philo, int i)
{
	while (i < philo->max_food_to_eat)
	{
		if (philo->butler->sebastien != 0)
		{
			philo->butler->dead_sig += 1;
			break ;
		}
		eat(philo);
		//philo->check_first_meal = 1;
		//check if all philos are dead then break
		/* if (philo->stop != 0) //if (philo->butler->sebastien != 0)
		{
			printf("seb != 0 mais %d\n", philo->stop);
			return ;
		} */
		sleeping(philo);
		think(philo);
		i++;
	}
}

void	*routine(void *phi)
{
	t_ph	*philo;
	int		i;
	//nvll struct mutex avec fct butler
	philo = (t_ph *) phi;
	usleep(250);
	if (philo->id % 2 == 0)
		usleep(100);
	print_state(philo, JOIN);
	i = 0;
	if (philo->max_food_to_eat != -1)
		execute_routine_with_limit_food(philo, i);
	else
		execute_routine(philo);
	return (0);
}

//fct qui check si philos ont mangé, envoyent chacun un signal OK

void	*check_dead(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = phi;
	while (1)
	{
		i = 0;
		while (i < philo[0].nb_philo)
		{
			if (time_between_meal(&philo[i]) > philo[i].time_die)
			{
				philo[i].butler->sebastien = 1;
				print_state(philo, DIE);
				break ;
			}
			i++;
		}
		if (philo[0].butler->sebastien != 0)
			break ;
	}
	return (0);
}

int	exec(t_ph *s_ph, pthread_t *philos, t_ph *tab_philos)
{
	pthread_t	*butler;
	int			i;

	i = 0;
	butler = malloc(sizeof(pthread_t));
	while (i < s_ph->nb_philo)
	{
		tab_philos[i] = *s_ph;
		tab_philos[i].id = i + 1;
		if (pthread_create(&philos[i], NULL, routine, &tab_philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(butler, NULL, check_dead, tab_philos) != 0)
		return (-1);
	i = 0;
	while (i < s_ph->nb_philo)
	{	
		if (pthread_join(philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(*butler, NULL) != 0)
		return (-1);
	pthread_mutex_destroy(&(s_ph->butler->mutex_write));
	i = 0;
	while (i < s_ph->butler->nb_forks)
	{
		pthread_mutex_destroy(&(s_ph->butler->forks[i]));
		i++;
	}
	free(butler);
	return (0);
}
