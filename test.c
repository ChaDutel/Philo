/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:43:11 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/11/30 17:42:38 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "test.h"

void	*eat(void *titou)
{
	(t_testi_testou *) titou;
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
}
