/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/11 13:23:26 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutex(t_ph *s_ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(s_ph->butler->mutex_write));
	while (i < s_ph->butler->nb_forks)
	{
		pthread_mutex_destroy(&(s_ph->butler->forks[i]));
		i++;
	}
}

int	join_pthread(t_ph *s_ph, pthread_t *butler, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < s_ph->nb_philo)
	{	
		if (pthread_join(philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(*butler, NULL) != 0)
		return (-1);
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
	if (join_pthread(s_ph, butler, philos) == -1)
		return (-1);
	destroy_mutex(s_ph);
	free(butler);
	return (0);
}
