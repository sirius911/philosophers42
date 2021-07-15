/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:01:06 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 12:01:08 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_philo(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->philo_pid)
		free(table->philo_pid);
}

int	delete_table(t_table *table)
{
	delete_semaphores(table);
	ending_philo(table);
	free_philo(table);
	return (FALSE);
}
