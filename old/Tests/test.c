/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/02 16:48:49 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <unistd.h>
#include <pthread.h>*/
#include "test.h"

/* void	*eat(t_testi_testou *titou)
{
	printf("Human n'%d is eating %d apples\n", titou->human, titou->apples);
}

void	*count_human(t_testi_testou *titou)
{
	if (titou->human == 0)
		printf("%d human joins\n", titou->human);
	else
		printf("%d humans join\n", titou->human);
}

int	main(int argc, char **argv)
{
	t_testi_testou	titou;
	pthread_t		test1;
	pthread_t		test2;
	int				human;
	int				apples;

	human = 0;
	apples = 80;
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
	return (0);
} */

void	*eat(void *ti)
{
	//*(t_testi_testou *) titou;
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	usleep(100);
	pthread_mutex_lock(&(titou.mutex_write));
	printf("Human n'%d is eating %d apples\n", titou.human, titou.apples);
	pthread_mutex_unlock(&(titou.mutex_write));
	return (0);
}

void	*count_human(void *ti)
{
	t_testi_testou	titou;

	titou = *(t_testi_testou *) ti;
	pthread_mutex_lock(&(titou.mutex_write));
	if (titou.human == 0)
		printf("%d human joins\n", titou.human);
	else
		printf("%d humans join\n", titou.human);
	pthread_mutex_unlock(&(titou.mutex_write));
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
}
