/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/04 12:16:01 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define JOIN 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct ph
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_food_to_eat;
	int				nb_philo;
	int				philo;
	//int				test_nb_philo;
	pthread_mutex_t	mutex_write;
}t_ph;

int		parse(int argc, char **argv);
int		init(int argc, char **argv, t_ph *s_ph);
int		exec(t_ph s_ph);
int		ft_atoi(const char *str);
int		check_min_values(t_ph *s_phi);

#endif