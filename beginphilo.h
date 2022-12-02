/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beginphilo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/02 21:41:06 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

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
	int				time_eat;
	int				time_sleep;
	int				nb_philo;
	int				test_nb_philo;
	pthread_mutex_t	mutex_write;
}t_ph;

#endif