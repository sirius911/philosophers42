/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:35:52 by clorin            #+#    #+#             */
/*   Updated: 2021/06/29 10:36:30 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	run_philo(t_table *table)
{
	int				i;
	pthread_t		thread;
	t_philosophe	*philosophe;

	i = 0;
	table->start_time = get_time();
	while (i < table->nb_philo)
	{
		philosophe = &table->philo[i];
		philosophe->birthday = table->start_time;
		if (pthread_create(&thread, NULL, &routine, (void *)philosophe) != 0)
			return (delete_table(table));
		pthread_detach(thread);
		i++;
	}
	return (TRUE);
}

static void	ending_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		*(&table->philo[i].stop) = TRUE;
		i++;
	}
}

static int	a_philo_is_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->philo[i].state == DEAD)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	main_loop(t_table *table)
{
	int	dead;

	dead = FALSE;
	while (!dead
		&& table->nb_finished_meal < table->nb_philo)
	{
		dead = a_philo_is_dead(table);
		usleep(T_MIN);
	}
	ending_philo(table);
	if (table->nb_finished_meal == table->nb_philo && !dead)
		printf("All philosophers ate %d meal(s) !\n", table->nb_meal);
}

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
