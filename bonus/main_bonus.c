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

static int	run_philo(t_table *table)
{
	int				i;
	pid_t			cur_pid;
	t_philosophe	*philosophe;

	i = 0;
	table->start_time = get_time();
	while (i < table->nb_philo)
	{
		philosophe = &table->philo[i];
		philosophe->birthday = table->start_time;
		cur_pid = fork();
		if (cur_pid == 0)
			routine(philosophe);
		else if (cur_pid != -1)
			table->philo_pid[i] = cur_pid;
		else
		{
			printf("Error\nCreating fork()\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	ending_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->philo_pid[i], SIGKILL);
		i++;
	}
}

static void	main_loop(t_table *table)
{
	int		stat_loc;
	int		nb_finished;

	nb_finished = 0;
	while (nb_finished < table->nb_philo)
	{
		waitpid(-1, &stat_loc, 0);
		if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == DEAD)
			break ;
		else if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) != DEAD)
			nb_finished++;
	}
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
		if (!run_philo(&table))
			return (delete_table(&table));
		main_loop(&table);
		delete_table(&table);
	}
	else
	{
		printf("Error.\nInvalid number of arguments :\n");
		return (usage(EXIT_FAILURE));
	}
	sleep(2);
	return (EXIT_SUCCESS);
}
