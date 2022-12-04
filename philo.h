/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/04 15:22:21 by cdutel-l         ###   ########.fr       */
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
	int				id;
	pthread_mutex_t	mutex_write;
}t_ph;

//////// PARSING ///////
int		parse(int argc, char **argv);
int		check_min_values(t_ph *s_phi);

//////// INIT    ///////
int		init_struc_elms(int argc, char **argv, t_ph *s_ph);
int		ft_atoi(const char *str);

//////// EXEC    ///////
int		exec(t_ph s_ph, pthread_t *philos, t_ph *tab_philos);

//////// STATE ///////
void	eat(t_ph philo);
void	sleeping(t_ph philo);
void	think(t_ph philo);
void	print_state(t_ph phi, int state);

#endif