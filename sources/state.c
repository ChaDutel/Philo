/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/18 19:49:30 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_action(t_ph *phi, int state)
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

int	print_state(t_ph *phi, int state)
{
	pthread_mutex_lock(&(phi->butler->mutex_write));
	if (state == DIE)
		printf("%lld %d died\n", (get_time() - phi->start_time), phi->id);
	pthread_mutex_lock(&(phi->butler->check_dead));
	if (phi->butler->sebastien != 0)
	{
		pthread_mutex_unlock(&(phi->butler->check_dead));
		pthread_mutex_unlock(&(phi->butler->mutex_write));
		return (-1);
	}
	else if (phi->butler->sebastien == 0)
		print_action(phi, state);
	pthread_mutex_unlock(&(phi->butler->check_dead));
	pthread_mutex_unlock(&(phi->butler->mutex_write));
	return (0);
}

int	think(t_ph *philo)
{
	if (print_state(philo, THINK) == -1)
		return (-1);
	return (0);
}

int	sleeping(t_ph *philo)
{
	if (print_state(philo, SLEEP) == -1)
		return (-1);
	ft_usleep(philo->time_sleep);
	return (0);
}

int	eat(t_ph *philo)
{
	int	left_fork;
	int	right_fork;

	right_fork = philo->id - 1;
	if (right_fork == 0)
		left_fork = philo->nb_philo - 1;
	else
		left_fork = philo->id - 2;
	take_fork(philo, RIGHT_HAND, right_fork);
	print_state(philo, TAKE_F);
	take_fork(philo, LEFT_HAND, left_fork);
	print_state(philo, TAKE_F);
	pthread_mutex_lock(&(philo->butler->time_lock[philo->id - 1]));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->butler->time_lock[philo->id - 1]));
	print_state(philo, EAT);
	ft_usleep(philo->time_eat);
	release_fork(philo, philo->right_hand, RIGHT_HAND, right_fork);
	release_fork(philo, philo->left_hand, LEFT_HAND, left_fork);
	return (0);
}
