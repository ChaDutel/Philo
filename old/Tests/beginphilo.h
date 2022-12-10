/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beginphilo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/03 17:26:56 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BEGINPHILO_H
# define BEGINPHILO_H

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
	int				nb_philo;
	int				philo;
	//int				test_nb_philo;
	pthread_mutex_t	mutex_write;
}t_ph;

int		parse(int argc, char **argv);
void	init(char **argv, t_ph *s_ph);
int		exec(t_ph s_ph);

#endif