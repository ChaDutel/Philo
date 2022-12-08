/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/06 18:40:02 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	execute_routine(t_ph philo)
{
	while (1)
	{
		eat(philo);
		if (philo.butler->sebastien != 0)
			return ;
		sleeping(philo);
		think(philo);
	}
}

void	execute_routine_with_limit_food(t_ph philo, int i)
{
	while (i < philo.max_food_to_eat)
	{
		eat(philo);
		//check if all philos are dead then break
		if (philo.butler->sebastien != 0)
			return ;
		sleeping(philo);
		think(philo);
		i++;
	}
}

void	*routine(void *phi)
{
	t_ph	philo;
	int		i;
	//nvll struct mutex avec fct butler

	philo = *(t_ph *) phi;
	usleep(250);
	if (philo.id % 2 == 0)
		usleep(100);
	print_state(philo, JOIN);
	i = 0;
	if (philo.max_food_to_eat != -1)
		execute_routine_with_limit_food(philo, i);
	else
		execute_routine(philo);
	return (0);
}

//fct qui check si philos ont mangé, envoyentc hacun un signal OK

int	exec(t_ph s_ph, pthread_t *philos, t_ph *tab_philos)
{
	int	i;

	i = 0;
	while (i < s_ph.nb_philo)
	{
		tab_philos[i] = s_ph;
		if (pthread_create(&philos[i], NULL, routine, &tab_philos[i]) != 0)
			return (-1);
		s_ph.id += 1;
		i++;
	}
	i = 0;
	while (i < s_ph.nb_philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&(s_ph.mutex_write));//!!
	//pthread_mutex_destroy(&(s_ph.butler->right_fork));
	//pthread_mutex_destroy(&(s_ph.butler->left_fork));
	i = 0;
	while (i < s_ph.butler->nb_forks)
	{
		pthread_mutex_destroy(&(s_ph.butler->forks[i]));
		i++;
	}
	//free(s_ph.butler->forks); //
	/* i = 0;
	while (i < s_ph.butler->nb_forks)
	{
		free(s_ph.butler->forks[i]);
		i++;
	} */
	return (0);
}

/* int	exec(t_ph s_ph, pthread_t *philos, t_ph *tab_philos)
{
	int	i;

	i = 0;
	while (i < s_ph.nb_philo)
	{
		tab_philos[i] = s_ph;
		if (pthread_create(&philos[i], NULL, routine, &tab_philos[i]) != 0)
			return (-1);
		s_ph.id += 1;
		i++;
	}
	i = 0;
	while (i < s_ph.nb_philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&(s_ph.mutex_write));//!!
	//pthread_mutex_destroy(&(s_ph.butler->right_fork));
	//pthread_mutex_destroy(&(s_ph.butler->left_fork));
	i = 0;
	while (i < s_ph.butler->nb_forks)
	{
		pthread_mutex_destroy(&(s_ph.butler->forks[i]));
		i++;
	}
	return (0);
 }*/

/* void	*routine(void *phi)
{
	t_ph	philo;
	int		i;

	philo = *(t_ph *) phi;
	usleep(250);
	print_state(philo, JOIN);
	if (philo.id % 2 == 0)
		usleep(100);
	i = 0;
	if (philo.max_food_to_eat != -1)
	{
		while (i < philo.max_food_to_eat)
		{
			eat(philo);
			sleeping(philo);
			think(philo);
			i++;
		}
	}
	else
	{
		while (1)
		{
			eat(philo);
			sleeping(philo);
			think(philo);
		}
	}
	return (0);
} */