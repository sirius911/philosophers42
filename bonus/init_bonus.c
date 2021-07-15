/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:47:48 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 11:47:52 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	init_philo(t_table *table)
{	
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i].num = i + 1;
		table->philo[i].table = table;
		table->philo[i].meal_taken = 0;
		table->philo[i].state = THINKING;
		i++;
	}	
}

static int	malloc_table(t_table *table)
{
	table->philo = (t_philosophe *) malloc(sizeof(t_philosophe)
			* table->nb_philo);
	if (!table->philo)
		return (FALSE);
	table->philo_pid = (pid_t *) malloc(sizeof(pid_t) * table->nb_philo);
	if (!table->philo_pid)
	{
		free_philo(table);
		return (FALSE);
	}
	return (TRUE);
}

int	init_table(t_table *table, char **argv, int limit_nb_eat)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->nb_forks = table->nb_philo;
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (limit_nb_eat)
		table->nb_meal = ft_atoi(argv[5]);
	else
		table->nb_meal = INT_MAX;
	table->a_philo_is_dead = FALSE;
	table->philo = NULL;
	table->philo_pid = NULL;
	if (!malloc_table(table))
	{
		printf("Error\n Allocation fail.\n");
		return (FALSE);
	}
	init_philo(table);
	return (init_semaphores(table));
}
