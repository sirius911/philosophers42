/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:30:25 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 12:30:51 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;
	long	start;

	start = split_time(0);
	if (argc >= 5 && argc <= 6)
	{
		if (!valid_arg(argv))
			return (EXIT_FAILURE);
		if (!init_table(&table, argv, argc == 6))
			return (EXIT_FAILURE);
		run_philo(&table);
		main_loop(&table);
		sleep(2);
		delete_table(&table);
	}
	else
	{
		printf("Error.\nInvalid number of arguments :\n");
		return (usage(EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
