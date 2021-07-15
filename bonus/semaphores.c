/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:05:47 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 12:05:49 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	unlock_semaphores(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_forks)
	{
		sem_post(table->forks);
		i++;
	}
	usleep(10000);
}

static void	unlink_semaphores(void)
{
	sem_unlink("forks");
	sem_unlink("printer");
}

int	delete_semaphores(t_table *table)
{
	unlock_semaphores(table);
	if (sem_close(table->forks) != 0)
		printf("Error\nsem_close(forks)\n");
	if (sem_close(table->printer) != 0)
		printf("Error\nsem_close(printer)\n");
	unlink_semaphores();
	return (FALSE);
}

int	init_semaphores(t_table *table)
{
	unlink_semaphores();
	table->forks = sem_open("forks", O_RDWR | O_CREAT,
			0664, table->nb_forks);
	if (table->forks == SEM_FAILED)
	{
		printf("Error\nOpening semaphore\n");
		return (delete_semaphores(table));
	}
	table->printer = sem_open("printer", O_RDWR | O_CREAT, 0664, 1);
	if (table->printer == SEM_FAILED)
	{
		printf("Error\nOpening semaphore\n");
		return (delete_semaphores(table));
	}
	return (TRUE);
}
