/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/18 03:28:04 by charline         ###   ########.fr       */
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
	pthread_mutex_lock(&(phi->butler->check_dead));
	if (state == DIE)
		printf("%lld %d died\n", (get_time() - phi->start_time), phi->id);
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
	usleep(philo->time_sleep);
	return (0);
}

void	take_fork(t_ph *philo, int i, int hand, int fork)
{
	if (i == 1)
		return ;
	else
	{
		pthread_mutex_lock(&(philo->butler->forks[fork]));
		if (philo->butler->tab_forks[fork] == 1)
		{
			if (hand == RIGHT_HAND)
				philo->right_hand = 1;
			else if (hand == LEFT_HAND)
				philo->left_hand = 1;
			philo->butler->tab_forks[fork] = 0;
		}
		pthread_mutex_unlock(&(philo->butler->forks[fork]));
	}
}
void	release_fork(t_ph *philo, int i, int hand, int fork)
{
	if (i == 0)
		return ;
	else
	{
		pthread_mutex_lock(&(philo->butler->forks[fork]));
		if (philo->butler->tab_forks[fork] == 0)
		{
			if (hand == RIGHT_HAND)
				philo->right_hand = 0;
			else if (hand == LEFT_HAND)
				philo->left_hand = 0;
			philo->butler->tab_forks[fork] = 1;
		}
		pthread_mutex_unlock(&(philo->butler->forks[fork]));
	}
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
	while (philo->right_hand != 1)
		take_fork(philo, philo->right_hand, RIGHT_HAND, right_fork);
	print_state(philo, TAKE_F);
	while (philo->left_hand != 1)
		take_fork(philo, philo->left_hand, LEFT_HAND, left_fork);
	print_state(philo, TAKE_F);
	print_state(philo, EAT);
	pthread_mutex_lock(&(philo->butler->time_lock[philo->id - 1]));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->butler->time_lock[philo->id - 1]));
	usleep(philo->time_eat);
	while (philo->right_hand != 0)
		release_fork(philo, philo->right_hand, RIGHT_HAND, right_fork);
	while (philo->left_hand != 0)
		release_fork(philo, philo->left_hand, LEFT_HAND, left_fork);
	return (0);
}
