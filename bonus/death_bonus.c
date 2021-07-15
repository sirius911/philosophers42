/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:46:58 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 13:47:00 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	waiting_death(t_philosophe *philo)
{
	while (philo->state != DEAD)
		;
	return (DEAD);
}

void	*control_death(void *data)
{
	t_philosophe	*philo;
	long			ts;

	philo = (t_philosophe *)data;
	while (philo->meal_taken < philo->table->nb_meal && philo->state != DEAD)
	{
		ts = split_time(philo->birthday);
		if ((philo->table->t_die < ts - philo->start_eat)
			&& philo->state != EATING)
		{
			print_philo(ts, philo->num, "\033[31m died\033[0m\n", philo);
			philo->state = DEAD;
			philo->meal_taken = philo->table->nb_meal;
			exit(DEAD);
		}
		usleep(T_MIN);
	}
	if (philo->state == DEAD)
		exit(DEAD);
	return (NULL);
}
