/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:17:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/18 18:58:44 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_fork(t_ph *philo, int hand, int fork)
{
	pthread_mutex_lock(&(philo->butler->forks[fork]));
	if (hand == RIGHT_HAND)
		philo->right_hand = 1;
	else if (hand == LEFT_HAND)
		philo->left_hand = 1;
	philo->butler->tab_forks[fork] = 0;
}

void	release_fork(t_ph *philo, int i, int hand, int fork)
{
	if (i == 0)
	{
		pthread_mutex_unlock(&(philo->butler->forks[fork]));
		return ;
	}
	else
	{
		if (hand == RIGHT_HAND)
			philo->right_hand = 0;
		else if (hand == LEFT_HAND)
			philo->left_hand = 0;
		philo->butler->tab_forks[fork] = 1;
		pthread_mutex_unlock(&(philo->butler->forks[fork]));
	}
}

void	release_all_fork(t_ph *philo)
{
	int	left_fork;
	int	right_fork;

	right_fork = philo->id - 1;
	if (right_fork == 0)
		left_fork = philo->nb_philo - 1;
	else
		left_fork = philo->id - 2;
	pthread_mutex_lock(&(philo->butler->forks[right_fork]));
	release_fork(philo, philo->right_hand, RIGHT_HAND, right_fork);
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));
	release_fork(philo, philo->left_hand, LEFT_HAND, left_fork);
}
