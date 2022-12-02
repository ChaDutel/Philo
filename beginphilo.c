/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beginphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/02 23:27:37 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "beginphilo.h"

void	print_state(t_ph phi, int state)
{
	pthread_mutex_lock(&(phi.mutex_write));
	if (state == JOIN)
		printf("Philosopher n'%d joins!\n", phi.test_nb_philo);
	/* else if (state == EAT)
		printf("Philosopher n'%d is eating\n", phi.human);
	else if (state == SLEEP)
		printf("Philospher n'%d is sleeping\n", phi.human);
	else if (state == THINK)
		printf("Philosopher n'%d is thinking\n", phi.human); */
	
	pthread_mutex_unlock(&(phi.mutex_write));
}

/* void	*think(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	print_state(titou, 5);
	return (0);
}


void	*sleeping(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	
	usleep(titou.time_sleep);
	print_state(titou, 4);
	return (0);
}

void	*eat(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	usleep(titou.time_eat);
	print_state(titou, 3);
	return (0);
} */

void	*create_philo(void *phi)
{
	t_ph	philos;

	philos = *(t_ph *) phi;
	print_state(philos, 1);
	return (0);
}

/* void	*do_smth(void *phi)
{
	pthread_t		test1;
	pthread_t		test2;
	pthread_t		test3;
	pthread_t		test4;
	if (pthread_create(&test1, NULL, count_human, &titou) != 0)
			return (-1);
		if (pthread_create(&test2, NULL, eat, &titou) != 0)
			return (-1);
		if (pthread_create(&test4, NULL, sleeping, &titou) != 0)
			return (-1);
		if (pthread_create(&test3, NULL, think, &titou) != 0)
			return (-1);
		if (pthread_join(test1, NULL) != 0)
			return (-1);
		if (pthread_join(test2, NULL) != 0)
			return (-1);
		if (pthread_join(test3, NULL) != 0)
			return (-1);
		if (pthread_join(test4, NULL) != 0)
			return (-1);
} */

int	main(int argc, char **argv)
{
	t_ph			s_ph;
	pthread_t		*philosophers;
	int				nb_philo;

	s_ph.nb_philo = 5;
	s_ph.time_eat = 3000;
	s_ph.time_sleep = 50 * 100;
	nb_philo = 0;
	s_ph.test_nb_philo = 0;
	philosophers = malloc(sizeof(pthread_t) * s_ph.nb_philo);
	pthread_mutex_init(&(s_ph.mutex_write), NULL);
	while (nb_philo < s_ph.nb_philo)
	{
		print_state(s_ph, JOIN);
		s_ph.test_nb_philo += 1;
		if (pthread_create(&philosophers[nb_philo], NULL, routine, &s_ph) != 0)
			return (-1);
		/*if (pthread_join(philosophers[i], NULL) != 0)
			return (-1); */
		nb_philo++;
	}	
	nb_philo = 0;
	while (nb_philo < s_ph.nb_philo)
	{
		/* if (pthread_create(&philosophers[i], NULL, do_smth, &s_ph) != 0)
			return (-1); */
		if (pthread_join(philosophers[nb_philo], NULL) != 0)
			return (-1);
		nb_philo++;
	}
	pthread_mutex_destroy(&(s_ph.mutex_write));
	return (0);
}

/* int	main(int argc, char **argv)
{
	t_ph			s_ph;
	pthread_t		philosophers;
	int				

	s_ph.nb_philo = 5;
	s_ph.time_eat = 3000;
	s_ph.time_sleep = 50 * 100;
	pthread_mutex_init(&(s_phi.mutex_write), NULL);
	while (1)
	{
		while  ()
		if (pthread_create(&philosophers, NULL, create_philo, &titou) != 0)
			return (-1);
		
		titou.human += 1;
	}
	pthread_mutex_destroy(&(titou.mutex_write));
	return (0);
} */

/* void	print_state(t_testi_testou titou, int state)
{
	pthread_mutex_lock(&(titou.mutex_write));
	if (state == 1)
		printf("%d human joins\n", titou.human);
	else if (state == 2)
		printf("%d humans join\n", titou.human);
	else if (state == 3)
		printf("Human n'%d is eating\n", titou.human);
	else if (state == 4)
		printf("Human n'%d is sleeping\n", titou.human);
	else if (state == 5)
		printf("Human n'%d is thinking\n", titou.human);
	
	pthread_mutex_unlock(&(titou.mutex_write));
}

void	*think(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	print_state(titou, 5);
	return (0);
}


void	*sleeping(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	
	usleep(titou.time_sleep);
	print_state(titou, 4);
	return (0);
}

void	*eat(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	usleep(titou.time_eat);
	print_state(titou, 3);
	return (0);
}

void	*count_human(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	if (titou.human == 0)
		print_state(titou, 1);
	else
		print_state(titou, 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_testi_testou	titou;
	pthread_t		test1;
	pthread_t		test2;
	pthread_t		test3;
	pthread_t		test4;

	titou.human = 0;
	titou.time_eat = 3000;
	titou.time_sleep = 50 * 100;
	pthread_mutex_init(&(titou.mutex_write), NULL);
	while (titou.human != 10)
	{
		if (pthread_create(&test1, NULL, count_human, &titou) != 0)
			return (-1);
		if (pthread_create(&test2, NULL, eat, &titou) != 0)
			return (-1);
		if (pthread_create(&test4, NULL, sleeping, &titou) != 0)
			return (-1);
		if (pthread_create(&test3, NULL, think, &titou) != 0)
			return (-1);
		if (pthread_join(test1, NULL) != 0)
			return (-1);
		if (pthread_join(test2, NULL) != 0)
			return (-1);
		if (pthread_join(test3, NULL) != 0)
			return (-1);
		if (pthread_join(test4, NULL) != 0)
			return (-1);
		titou.human += 1;
	}
	pthread_mutex_destroy(&(titou.mutex_write));
	return (0);
} */