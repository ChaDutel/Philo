/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/12 17:59:18 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_ph *phi, int state)
{
	pthread_mutex_lock(&(phi->butler->mutex_write));
	if (state == DIE)
		printf("%ld %d died\n", (phi->current_m - phi->ml_start), phi->id);
	else if (phi->butler->sebastien == 0)
	{
		if (state == JOIN)
			printf("%ld %d joins!\n", (phi->current_m - phi->ml_start), phi->id);
		else if (state == EAT)
			printf("%ld %d is eating\n", \
			(phi->current_m - phi->ml_start), phi->id);
		else if (state == TAKE_F)
			printf("%ld %d has taken a fork\n", \
			(phi->current_m - phi->ml_start), phi->id);
		else if (state == SLEEP)
			printf("%ld %d is sleeping\n", \
			(phi->current_m - phi->ml_start), phi->id);
		else if (state == THINK)
			printf("%ld %d is thinking\n", \
			(phi->current_m - phi->ml_start), phi->id);
	}
	pthread_mutex_unlock(&(phi->butler->mutex_write));
}

void	think(t_ph *philo)
{
	print_state(philo, THINK);
}

void	sleeping(t_ph *philo)
{
	print_state(philo, SLEEP);
	usleep(philo->time_sleep);
}

void	eat(t_ph *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	if (philo->id == 1)
		left_fork = philo->nb_philo - 1;
	pthread_mutex_lock(&(philo->butler->forks[philo->id]));
	print_state(philo, TAKE_F);
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));
	print_state(philo, TAKE_F);
	print_state(philo, EAT);
	usleep(philo->time_eat);
	time_last_meal(philo);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
}

/* void	eat(t_ph *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	if (philo->id == 1)
		left_fork = philo->nb_philo - 1;
	if (philo->id == philo->nb_philo || philo->id == 1)
	{
		if (philo->butler->dead_sig % 2 == 0 && philo->id == philo->nb_philo)
		{
			pthread_mutex_lock(&(philo->butler->forks[philo->id]));
			pthread_mutex_lock(&(philo->butler->forks[left_fork]));
			//usleep(10);
		}
		else if (philo->butler->dead_sig % 2 != 0 && philo->id == 1)
		{
			pthread_mutex_lock(&(philo->butler->forks[philo->id]));
			pthread_mutex_lock(&(philo->butler->forks[left_fork]));
			//usleep(10);
		}
		philo->butler->dead_sig += 1;
	}
	else
	{
		pthread_mutex_lock(&(philo->butler->forks[philo->id]));
		pthread_mutex_lock(&(philo->butler->forks[left_fork]));
		// printf("%d\n", time_between_meal(philo));
		// printf("%d\n", philo->time_die);
	}
	usleep(philo->time_eat);
	print_state(philo, EAT);
	time_last_meal(philo);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
} */

/* void	eat(t_ph *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	if (philo->id == 1)
		left_fork = philo->nb_philo - 1;
	if (philo->id == philo->nb_philo || philo->id == 1)
	{
		if (philo->butler->dead_sig % 2 == 0 && philo->id == philo->nb_philo)
			usleep(10);
		else if (philo->butler->dead_sig % 2 != 0 && philo->id == 1)
			usleep(10);
		philo->butler->dead_sig += 1;
	}
	pthread_mutex_lock(&(philo->butler->forks[philo->id]));
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));
	// printf("%d\n", time_between_meal(philo));
	// printf("%d\n", philo->time_die);
	usleep(philo->time_eat);
	print_state(philo, EAT);
	time_last_meal(philo);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
} */
