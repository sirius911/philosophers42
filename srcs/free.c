/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:39:31 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 10:39:48 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo(t_table *table)
{
	if (table->philo)
		free(table->philo);
}

void	free_forks(t_table *table)
{
	if (table->forks)
		free(table->forks);
}

int	free_mutex(t_table *table)
{
	int	i;

	pthread_mutex_unlock(&table->printer);
	pthread_mutex_destroy(&table->printer);
	pthread_mutex_unlock(&table->finished_meal);
	pthread_mutex_destroy(&table->finished_meal);
	i = 0;
	while (i < table->nb_forks)
	{
		if (pthread_mutex_destroy(&table->forks[i]) == EBUSY)
		{
			pthread_mutex_unlock(&table->forks[i]);
			pthread_mutex_destroy(&table->forks[i]);
		}
		i++;
	}
	return (FALSE);
}

int	delete_table(t_table *table)
{
	free_mutex(table);
	free_forks(table);
	free_philo(table);
	return (FALSE);
}
