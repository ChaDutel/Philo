/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:28:14 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/03 17:29:55 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_pars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(int argc, char **argv)
{
	if (argc != 5)
	{
		write(2, "Wrong number of paramaters\n", 27);
		return (-1);
	}
	if (check_pars(argv) == -1)
	{
		write(2, "Wrong parameters\n", 17);
		return (-1);
	}
	return (0);
}
