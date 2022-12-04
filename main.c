/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:12:19 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/12/04 12:16:08 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ph	phi;

	if (parse(argc, argv) == -1)
		return (0);
	if (init(argc, argv, &phi) == -1)
		return (0);
	exec(phi);
}
