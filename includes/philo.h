/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/15 16:44:31 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define DIE 1
# define EAT 2
# define TAKE_F 3
# define SLEEP 4
# define THINK 5

typedef struct s_butler
{
	int				sebastien;
	int				nb_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_write;
	int				*tab_forks;
	// pthread_mutex_t	time_lock;
	// pthread_mutex_t	check_dead;
}	t_butler;

typedef struct s_ph
{
	unsigned long long	time_die;
	long long			time_eat;
	long long			time_sleep;
	int					max_food_to_eat;
	int					nb_philo;
	int					id;
	t_butler			*butler;
	int					food;
	unsigned long long	ml_start;
	unsigned long long	last;
}	t_ph;

//////// PARSING ///////
int					parse(int argc, char **argv);
int					check_min_values(t_ph *s_phi);

//////// INIT    ///////
int					init_struc_elms(int argc, char **argv, t_ph *s_ph);
long long			ft_atoi(const char *str);

//////// INIT TIME /////
void				init_time_begin(t_ph *s_ph);
void				time_last_meal(t_ph *s_ph);
unsigned long long	get_time(void);

//////// EXEC    ///////
int					exec(t_ph *s_ph, pthread_t *philos, t_ph *tab_philos);
void				ft_usleep(long long time);

//////// ROUTINE ///////
void				*check_dead(void *phi);
void				*routine(void *phi);

//////// STATE  ///////
void				eat(t_ph *philo);
void				sleeping(t_ph *philo);
void				think(t_ph *philo);
void				print_state(t_ph *phi, int state);

#endif