/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/08 11:11:26 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_ph phi, int state)
{
	usleep(5000);
	pthread_mutex_lock(&(phi.mutex_write));
	if (state == JOIN)
		printf("Philosopher n'%d joins!\n", phi.id);
	else if (state == EAT)
		printf("Philosopher n'%d is eating\n", phi.id);
	else if (state == SLEEP)
		printf("Philospher n'%d is sleeping\n", phi.id);
	else if (state == THINK)
		printf("Philosopher n'%d is thinking\n", phi.id);
	pthread_mutex_unlock(&(phi.mutex_write));
}

void	think(t_ph philo)
{
	print_state(philo, THINK);
}

void	sleeping(t_ph philo)
{
	usleep(philo.time_sleep);
	print_state(philo, SLEEP);
}

void	eat(t_ph philo)
{
	pthread_mutex_lock(&(philo.butler->forks[philo.id]));
	if ((philo.id - 1) < 1)
	{
		pthread_mutex_lock(&(philo.butler->forks[philo.nb_philo - 1]));
		if ((time_between_meal(&philo) < philo.time_die) && philo.check_first_meal != -1)
		{
			printf("philo n'%d diiiiiiiiiiiiiiiiiiiiie\n", philo.id);
			philo.butler->sebastien = 1;
			pthread_mutex_unlock(&(philo.butler->forks[philo.nb_philo - 1]));
			pthread_mutex_unlock(&(philo.butler->forks[philo.id]));
			return ;
		}
		usleep(philo.time_eat);
		print_state(philo, EAT);
		time_last_meal(&philo);
		philo.check_first_meal = 1;
		pthread_mutex_unlock(&(philo.butler->forks[philo.nb_philo - 1]));
	}
	else
	{
		pthread_mutex_lock(&(philo.butler->forks[philo.id - 1]));
		if ((time_between_meal(&philo) < philo.time_die) && philo.check_first_meal != -1)
		{
			printf("philo n'%d diiiiiiiiiiiiiiiiiiiiie\n", philo.id);
			philo.butler->sebastien = 1;
			pthread_mutex_unlock(&(philo.butler->forks[philo.nb_philo - 1]));
			pthread_mutex_unlock(&(philo.butler->forks[philo.id]));
			return ;
		}
		usleep(philo.time_eat);
		print_state(philo, EAT);
		time_last_meal(&philo);
		philo.check_first_meal = 1;
		pthread_mutex_unlock(&(philo.butler->forks[philo.id - 1]));
	}
	pthread_mutex_unlock(&(philo.butler->forks[philo.id]));
	//print_state(philo, EAT); //test
}
