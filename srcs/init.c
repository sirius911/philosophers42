/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:04:05 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 11:04:20 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		table->philo[i].stop = FALSE;
		table->philo[i].left_fork = &table->forks[i];
		if (i == 0)
			table->philo[i].right_fork = &table->forks[table->nb_philo - 1];
		else
			table->philo[i].right_fork = &table->forks[i - 1];
		i++;
	}	
}

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->flag_finished_meal, NULL) != 0)
	{
		printf("Error\nInit mutex error\n");
		return (free_mutex(table));
	}
	while (i < table->nb_forks)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("Error\nInit mutex error\n");
			return (free_mutex(table));
		}
		i++;
	}
	return (TRUE);
}

static int	init_printer(t_table *table)
{
	if (pthread_mutex_init(&table->printer, NULL) != 0)
	{
		printf("Error\nInit mutex error\n");
		return (free_mutex(table));
	}
	return (TRUE);
}

static int	malloc_table(t_table *table)
{
	table->philo = (t_philosophe *) malloc(sizeof(t_philosophe)
			* table->nb_philo);
	if (!table->philo)
		return (FALSE);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->nb_forks);
	if (!table->forks)
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
	table->nb_finished_meal = 0;
	table->philo = NULL;
	table->forks = NULL;
	if (!malloc_table(table))
	{
		printf("Error\n Allocation fail.\n");
		return (FALSE);
	}
	init_philo(table);
	return (init_forks(table) && init_printer(table));
}
