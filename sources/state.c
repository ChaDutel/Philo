/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/15 16:48:09 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// pthread_mutex_init(&(s_ph->butler->check_dead), NULL);
// pthread_mutex_init(&(s_ph->butler->time_lock), NULL);

void	print_state(t_ph *phi, int state)
{
	pthread_mutex_lock(&(phi->butler->mutex_write));
	//pthread_mutex_lock(&(phi->butler->check_dead));
	if (state == DIE)
	{
		//pthread_mutex_unlock(&(phi->butler->check_dead));
		printf("%llu %d died\n", (get_time() - phi->ml_start), phi->id);
	}
	else if (phi->butler->sebastien == 0)
	{
		//pthread_mutex_unlock(&(phi->butler->check_dead));
		if (state == EAT)
			printf("%llu %d is eating\n", \
			(get_time() - phi->ml_start), phi->id);
		else if (state == TAKE_F)
			printf("%llu %d has taken a fork\n", \
			(get_time() - phi->ml_start), phi->id);
		else if (state == SLEEP)
			printf("%llu %d is sleeping\n", \
			(get_time() - phi->ml_start), phi->id);
		else if (state == THINK)
			printf("%llu %d is thinking\n", \
			(get_time() - phi->ml_start), phi->id);
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
	// ft_usleep(philo->time_sleep);
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
	pthread_mutex_lock(&(philo->butler->forks[left_fork]));
	print_state(philo, TAKE_F);
	philo->butler->tab_forks[left_fork] = 0;
	pthread_mutex_lock(&(philo->butler->forks[right_fork]));
	print_state(philo, TAKE_F);
	philo->butler->tab_forks[right_fork] = 0;
	print_state(philo, EAT);
	// ft_usleep(philo->time_eat);
	usleep(philo->time_eat);
	time_last_meal(philo);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	philo->butler->tab_forks[left_fork] = 1;
	pthread_mutex_unlock(&(philo->butler->forks[right_fork]));
	philo->butler->tab_forks[right_fork] = 1;
}

/* void	eat(t_ph *philo)
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
	// usleep(philo->time_eat);
	ft_usleep(philo->time_eat);
	time_last_meal(philo);
	pthread_mutex_unlock(&(philo->butler->forks[left_fork]));
	pthread_mutex_unlock(&(philo->butler->forks[philo->id]));
} */
