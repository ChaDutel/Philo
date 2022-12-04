/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:28:14 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/04 12:37:46 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_min_values(t_ph *s_ph)
{
	if (s_ph->nb_philo <= 1 || s_ph->time_die < 2000 || s_ph->time_eat < 2000 \
		|| s_ph->time_sleep < 2000)
	{
		if (s_ph->nb_philo < 1)
			write(2, "Too few philosophers\n", 21);
		else if (s_ph->nb_philo == 1)
		{
			write(2, "Philosopher n'1 dies, he ", 25);
			write(2, "couldn't eat with one fork...\n", 30);
		}
		else if (s_ph->time_die < 2000)
			write(2, "Time to die is too short\n", 25);
		else if (s_ph->time_eat < 2000)
			write(2, "Time to eat is too short\n", 25);
		else if (s_ph->time_sleep < 2000)
			write(2, "Time to sleep is too short\n", 27);
		return (-1);
	}
	else
		return (0);
}

int	check_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '-')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of paramaters\n", 27);
		return (-1);
	}
	if (check_num(argv) == -1)
	{
		write(2, "Wrong parameters\n", 17);
		return (-1);
	}
	return (0);
}
