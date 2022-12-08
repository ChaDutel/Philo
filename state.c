/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/08 16:16:43 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_ph *phi, int state)
{
	//usleep(5000);
	pthread_mutex_lock(&(phi->butler->mutex_write));
	if (state == JOIN)
		printf("Philosopher n'%d joins!\n", phi->id);
	else if (state == EAT)
		printf("Philosopher n'%d is eating\n", phi->id);
	else if (state == SLEEP)
		printf("Philospher n'%d is sleeping\n", phi->id);
	else if (state == THINK)
		printf("Philosopher n'%d is thinking\n", phi->id);
	pthread_mutex_unlock(&(phi->butler->mutex_write));
}

void	think(t_ph *philo)
{
	print_state(philo, THINK);
}

void	sleeping(t_ph *philo)
{
	usleep(philo->time_sleep);
	print_state(philo, SLEEP);
}

/* unsigned long get_time()
{
	return sec * 1000 + usce / 1000;
}

void	ft_usleep(t_ph *ph, unsigned int time_to_dead, unsigned int time)
{
	unsigned long futur;

	futur = get_time() + time;
	while (get_time() < futur)
	{

		usleep(500);
	}
} */

void	eat(t_ph *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	if (philo->id == 1)
		left_fork = philo->nb_philo - 1;
	pthread_mutex_lock(&(philo->butler->forks[philo->id]));
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));////////
	if (time_between_meal(philo) > philo->time_die)
	{
		printf("philo n'%d diiiiiiiiiiiiiiiiiiiiie\n", philo->id);
		philo->butler->sebastien = 1;
		pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
		pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
		return ;
	}
	printf("%d\n", time_between_meal(philo));
	printf("%d\n", philo->time_die);
	usleep(philo->time_eat);
	print_state(philo, EAT);
	time_last_meal(philo);
	//printf("%d\n", philo->check_first_meal);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
}
