/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:15:39 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/06 15:21:40 by cdutel-l         ###   ########.fr       */
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

/* int main() {
 
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
 
  for (int i = 0; i <1e5 ; i++) {
  }
 
  gettimeofday(&end, NULL);
  printf("Time taken to count to 10^5 is : %ld micro seconds\n",
    ((end.tv_sec * 1000000 + end.tv_usec) -
    (start.tv_sec * 1000000 + start.tv_usec)));

  return 0;
}*/

void	eat(t_ph philo)
{
	pthread_mutex_lock(&(philo.butler->forks[philo.id]));
	if ((philo.id - 1) < 1)
	{
		pthread_mutex_lock(&(philo.butler->forks[philo.nb_philo - 1]));
		usleep(philo.time_eat);
		print_state(philo, EAT);
		pthread_mutex_unlock(&(philo.butler->forks[philo.nb_philo - 1]));
	}
	else
	{
		pthread_mutex_lock(&(philo.butler->forks[philo.id - 1]));
		usleep(philo.time_eat);
		print_state(philo, EAT);
		pthread_mutex_unlock(&(philo.butler->forks[philo.id - 1]));
	}
	pthread_mutex_unlock(&(philo.butler->forks[philo.id]));
	//print_state(philo, EAT); //test
}
