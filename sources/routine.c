/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:22:40 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/17 23:13:28 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	release_all_fork(t_ph *philo)
{
	int	left_fork;
	int	right_fork;

	right_fork = philo->id - 1;
	if (right_fork == 0)
		left_fork = philo->nb_philo - 1;
	else
		left_fork = philo->id - 2;
	while (philo->right_hand != 0 || philo->left_hand != 0)
	{
		release_fork(philo, philo->right_hand, RIGHT_HAND, right_fork);
		release_fork(philo, philo->left_hand, LEFT_HAND, left_fork);
	}
}

void	execute_routine(t_ph *philo)
{
	while (1)
	{
		eat(philo);
		if (sleeping(philo) == -1)
			break ;
		if (think(philo) == -1)
			break ;
	}
	release_all_fork(philo);
	printf("hello %d\n", philo->id);
}

/* void	execute_routine(t_ph *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		eat(philo);
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		sleeping(philo);
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			printf("%d\n", philo->id);
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		think(philo);
	}
} */

/* void	execute_routine_with_limit_food(t_ph *philo, int i)
{
	while (i < philo->max_food_to_eat)
	{
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		eat(philo);
		// pthread_mutex_lock(&(philo->butler->food_lock));
		philo->nb_food_eaten += 1;
		// pthread_mutex_unlock(&(philo->butler->food_lock));
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		sleeping(philo);
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo->butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			return ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
		think(philo);
		i++;
	}
} */

void	execute_routine_with_limit_food(t_ph *philo, int i)
{
	while (i < philo->max_food_to_eat)
	{
		eat(philo);
		pthread_mutex_lock(&(philo->butler->food_lock));
		philo->nb_food_eaten += 1;
		// if (philo->nb_food_eaten == philo->max_food_to_eat)
		// 	ger++;
		pthread_mutex_unlock(&(philo->butler->food_lock));
		if (sleeping(philo) == -1)
			break ;
		if (think(philo) == -1)
			break ;
		i++;
	}
	/*  += 1;
	 execute_routine */
	release_all_fork(philo);
}

void	execute_routine_for_one(t_ph *philo)
{
	print_state(philo, TAKE_F);
	usleep(philo->time_die);
}

void	*routine(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = (t_ph *) phi;
	if (philo->id % 2 == 0)
		usleep(500);
	//print_state(philo, JOIN);
	i = 0;
	if (philo->nb_philo == 1)
		execute_routine_for_one(philo);
	else if (philo->max_food_to_eat != -1)
		execute_routine_with_limit_food(philo, i);
	else
		execute_routine(philo);
	return (0);
}

void	*check_dead(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = phi;
	while (1)
	{
		usleep(2000);
		i = 0;
		while (i < philo[0].nb_philo)
		{
			pthread_mutex_lock(&(philo->butler->time_lock));
			if (((get_time() - philo[i].last_meal) * 1000) > (unsigned long long)philo[i].time_die)
			{
				pthread_mutex_unlock(&(philo->butler->time_lock));
				pthread_mutex_lock(&(philo->butler->check_dead));
				philo[i].butler->sebastien = 1;
				pthread_mutex_unlock(&(philo->butler->check_dead));
				pthread_mutex_lock(&(philo->butler->food_lock));
				if (philo[i].nb_food_eaten != philo[i].max_food_to_eat) // <
				{
					
					// printf("%d %d\n", philo[i].id, philo[i].nb_food_eaten);
					if (print_state(&philo[i], DIE) == -1)
					{
						pthread_mutex_unlock(&(philo->butler->food_lock));
						/* //usleep(2000000);
						for (int j = 0; j < philo[i].butler->nb_forks; j++)
							printf("Fork %d: %d\n", j, philo[i].butler->tab_forks[j]); */
						return (0);
					}
				}
				pthread_mutex_unlock(&(philo->butler->food_lock));
				//break ;
				return (0);
			}
			pthread_mutex_unlock(&(philo->butler->time_lock));
			i++;
		}
		i = 0;
		/* if (philo[i].max_food_to_eat != -1)
		{
			while (i < philo[0].nb_philo && philo[i]->nb_food_eaten == philo[i].max_food_to_eat)
			{
				
			}
		} */
		pthread_mutex_lock(&(philo->butler->check_dead));
		if (philo[0].butler->sebastien != 0)
		{
			pthread_mutex_unlock(&(philo->butler->check_dead));
			break ;
		}
		pthread_mutex_unlock(&(philo->butler->check_dead));
	}
	return (0);
}
