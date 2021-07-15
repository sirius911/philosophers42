/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:34:51 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 13:34:53 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	take_forks(t_philosophe *philo)
{
	sem_wait(philo->table->forks);
	print_philo(split_time(philo->birthday),
		philo->num, "\033[33m has taken a fork\033[0m\n", philo);
	sem_post(philo->table->printer);
	if (philo->table->nb_philo == 1)
		return (waiting_death(philo));
	else
	{
		sem_wait(philo->table->forks);
		print_philo(split_time(philo->birthday),
			philo->num, "\033[33m has taken a fork\033[0m\n", philo);
		sem_post(philo->table->printer);
	}
	return (TRUE);
}

static void	eating(t_philosophe *philo)
{
	if (philo->state != DEAD)
	{
		if (take_forks(philo))
		{
			philo->state = EATING;
			philo->meal_taken++;
			philo->start_eat = split_time(philo->birthday);
			print_philo(philo->start_eat, philo->num,
				"\033[32m is eating\033[0m\n", philo);
			sem_post(philo->table->printer);
			usleep(philo->table->t_eat * 1000);
			sem_post(philo->table->forks);
			sem_post(philo->table->forks);
		}
	}
}

static void	sleeping(t_philosophe *philo)
{
	if (philo->state != DEAD)
	{
		philo->state = SLEEPING;
		print_philo(split_time(philo->birthday),
			philo->num, "\033[34m is sleeping\033[0m\n", philo);
		sem_post(philo->table->printer);
		usleep(philo->table->t_sleep * 1000);
	}
}

static void	thinking(t_philosophe *philo)
{
	if (philo->state != DEAD)
	{
		philo->state = THINKING;
		print_philo(split_time(philo->birthday),
			philo->num, "\033[36m is thinking\033[0m\n", philo);
		sem_post(philo->table->printer);
	}
}

int	routine(t_philosophe *philo)
{
	pthread_t		death_control;

	philo->start_eat = 0;
	if (pthread_create(&death_control, NULL, &control_death, philo))
	{
		printf("Error\n creating pthread\n");
		return (FALSE);
	}
	pthread_detach(death_control);
	while (philo->state != DEAD
		&& philo->meal_taken < philo->table->nb_meal)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(T_MIN);
	}
	sem_close(philo->table->forks);
	sem_close(philo->table->printer);
	exit(philo->state);
}
