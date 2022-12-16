/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/16 15:42:01 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_ph *phi, int state)
{
	pthread_mutex_lock(&(phi->butler->mutex_write));
	if (state == DIE)
		printf("%lld %d died\n", (get_time() - phi->start_time), phi->id);
	else if (phi->butler->sebastien == 0)
	{
		if (state == EAT)
			printf("%lld %d is eating\n", \
			(get_time() - phi->start_time), phi->id);
		else if (state == TAKE_F)
			printf("%lld %d has taken a fork\n", \
			(get_time() - phi->start_time), phi->id);
		else if (state == SLEEP)
			printf("%lld %d is sleeping\n", \
			(get_time() - phi->start_time), phi->id);
		else if (state == THINK)
			printf("%lld %d is thinking\n", \
			(get_time() - phi->start_time), phi->id);
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
	int	right_fork;

	right_fork = philo->id - 1;
	if (right_fork == 0)
		left_fork = philo->nb_philo - 1;
	else
		left_fork = philo->id - 2;
	pthread_mutex_lock(&(philo->butler->forks[right_fork]));
	print_state(philo, TAKE_F);
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));
	print_state(philo, TAKE_F);
	print_state(philo, EAT);
	// ft_usleep(philo->time_eat);
	usleep(philo->time_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->butler->forks[right_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
}
