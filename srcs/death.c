/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:35:33 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 10:35:39 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	waiting_death(t_philosophe *philo)
{
	while (philo->state != DEAD)
		;
	return (FALSE);
}

void	*control_death(void *data)
{
	t_philosophe	*philo;
	long			ts;

	philo = (t_philosophe *)data;
	while (philo->meal_taken < philo->table->nb_meal && philo->state != DEAD
		&& !philo->stop)
	{
		ts = split_time(philo->birthday);
		if ((philo->table->t_die < ts - philo->start_eat)
			&& philo->state != EATING)
		{
			if (!philo->stop)
				print_philo(ts, philo->num, "\033[31m died\033[0m\n", philo);
			philo->state = DEAD;
			philo->stop = TRUE;
			break ;
		}
		usleep(T_MIN);
	}
	return (NULL);
}
