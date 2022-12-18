/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:12:19 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/18 03:19:34 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_ph phi, pthread_t *philos, t_ph *tab_philos)
{
	free(tab_philos);
	free(phi.butler->forks);
	free(phi.butler->time_lock);
	free(phi.butler->tab_forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	pthread_t		*philosophers;
	t_ph			phi;
	t_ph			*tab_philos;
	t_butler		butler;

	phi.butler = &butler;
	if (parse(argc, argv) == -1)
		return (0);
	if (init_struc_elms(argc, argv, &phi) == -1)
		return (0);
	philosophers = malloc(sizeof(pthread_t) * phi.nb_philo);
	if (!philosophers)
	{
		free(phi.butler->forks);
		free(phi.butler->tab_forks);
		free(phi.butler->time_lock);
		return (0);
	}
	tab_philos = malloc(sizeof(t_ph) * phi.nb_philo);
	if (!tab_philos)
	{
		free(phi.butler->forks);
		free(phi.butler->tab_forks);
		free(phi.butler->time_lock);
		free(philosophers);
		return (0);
	}
	exec(&phi, philosophers, tab_philos);
	ft_free(phi, philosophers, tab_philos);
}
