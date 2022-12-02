/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/02 20:34:22 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test2.h"

void	print_state(t_testi_testou titou, int state)
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
}

/* void	print_state(t_testi_testou titou, int state)
{
	pthread_mutex_lock(&(titou.mutex_write));
	if (state == 1)
		printf("%d human joins\n", titou.human);
	else if (state == 2)
		printf("%d humans join\n", titou.human);
	else if (state == 3)
		printf("Human n'%d is eating %d apples\n", titou.human, titou.apples);
	
	pthread_mutex_unlock(&(titou.mutex_write));
}

void	*eat(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	usleep(100);
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
	pthread_mutex_t	mutex_write;
	int				human;
	int				apples;

	human = 0;
	apples = 80;
	titou.mutex_write = mutex_write;
	pthread_mutex_init(&(titou.mutex_write), NULL);
	while (human != 10)
	{
		titou.apples = apples;
		titou.human = human;
		if (pthread_create(&test1, NULL, count_human, &titou) != 0)
			return (-1);
		if (pthread_create(&test2, NULL, eat, &titou) != 0)
			return (-1);
		if (pthread_join(test1, NULL) != 0)
			return (-1);
		if (pthread_join(test2, NULL) != 0)
			return (-1);
		apples -= 10;
		human++;
	}
	pthread_mutex_destroy(&(titou.mutex_write));
	return (0);
} */
