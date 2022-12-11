/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:12:19 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/11 18:53:09 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	pthread_t		*philosophers;
	t_ph			phi;
	t_ph			*tab_philos;
	t_butler		butler;
	t_time			time;

	phi.butler = &butler;
	phi.time = &time;
	if (parse(argc, argv) == -1)
		return (0);
	if (init_struc_elms(argc, argv, &phi) == -1)
		return (0);
	philosophers = malloc(sizeof(pthread_t) * phi.nb_philo);
	if (!philosophers)
	{
		free(phi.butler->forks);
		return (0);
	}
	tab_philos = malloc(sizeof(t_ph) * phi.nb_philo);
	if (!tab_philos)
	{
		free(phi.butler->forks);
		free(philosophers);
		return (0);
	}
	exec(&phi, philosophers, tab_philos);
	free(philosophers);
	free(tab_philos);
	free(phi.butler->forks);
}