/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:23 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/08 11:10:16 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define JOIN 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_time
{
	//struct timeval	*start;
	long				ml_start;
	//struct timeval	*first_or_previous_meal;
	long				first_o_pr_m;
	//struct timeval	*current_meal;
	long				current_m;
	//long				t_between_meals;
}	t_time;

typedef struct s_butler
{
	int				sebastien;
	int				nb_forks;
	pthread_mutex_t	*forks;
	//int			time_between_eat_and_die;
	//int			time_start
	//int				fork;
	//pthread_mutex_t	right_fork;
	//pthread_mutex_t	left_fork;
}	t_butler;

typedef struct s_ph
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_food_to_eat;
	int				nb_philo;
	int				id;
	int				check_first_meal;
	pthread_mutex_t	mutex_write;
	t_butler		*butler;
	t_time			*time;
}	t_ph;

//////// PARSING ///////
int		parse(int argc, char **argv);
int		check_min_values(t_ph *s_phi);

//////// INIT    ///////
int		init_struc_elms(int argc, char **argv, t_ph *s_ph);
int		ft_atoi(const char *str);

//////// INIT TIME /////
void	init_time_begin(t_ph *s_ph);
void	time_last_meal(t_ph *s_ph);
int		time_between_meal(t_ph *s_ph);

//////// EXEC    ///////
int		exec(t_ph s_ph, pthread_t *philos, t_ph *tab_philos);

//////// STATE ///////
void	eat(t_ph philo);
void	sleeping(t_ph philo);
void	think(t_ph philo);
void	print_state(t_ph phi, int state);

#endif