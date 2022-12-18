/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/18 19:01:23 by cdutel-l         ###   ########.fr       */
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
# define RIGHT_HAND 6
# define LEFT_HAND 7

typedef struct s_butler
{
	int				sebastien;
	int				nb_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_write;
	int				*tab_forks;
	pthread_mutex_t	*time_lock;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	lock_all_meal;
	int				eat_all_meal;
}	t_butler;

typedef struct s_ph
{
	long long			time_die;
	long long			time_eat;
	long long			time_sleep;
	int					max_food_to_eat;
	int					nb_philo;
	int					id;
	t_butler			*butler;
	int					nb_food_eaten;
	unsigned long long	start_time;
	unsigned long long	last_meal;
	int					right_hand;
	int					left_hand;
}	t_ph;

//////// PARSING ///////
int				parse(int argc, char **argv);
int				check_min_values(t_ph *s_ph, int argc, char **argv);
int				check_max_values(t_ph *s_ph);

//////// INIT    ///////
int				init_struc_elms(int argc, char **argv, t_ph *s_ph);
long long		ft_atoi(const char *str);

//////// EXEC    ///////
int				exec(t_ph *s_ph, pthread_t *philos, t_ph *tab_philos);

//////// ROUTINE ///////
void			*check_dead(void *phi);
void			*routine(void *phi);

//////// STATE  ////////
int				eat(t_ph *philo);
int				sleeping(t_ph *philo);
int				think(t_ph *philo);
int				print_state(t_ph *phi, int state);

//////// FORKS  ////////
void			release_all_fork(t_ph *philo);
// void			release_fork(t_ph *philo, int i, int fork);
void			release_fork(t_ph *philo, int i, int hand, int fork);
// void			take_fork(t_ph *philo, int fork);
void			take_fork(t_ph *philo, int hand, int fork);

//////// UTILS  ////////
long long		get_time(void);
void			ft_usleep(long long time);

#endif