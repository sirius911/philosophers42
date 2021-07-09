/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:48:36 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 10:25:17 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philosophe *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		print_philo(split_time(philo->birthday),
			philo->num, "\033[33m has taken a fork\033[0m\n", philo);
		pthread_mutex_lock(philo->left_fork);
		print_philo(split_time(philo->birthday),
			philo->num, "\033[33m has taken a fork\033[0m\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo(split_time(philo->birthday),
			philo->num, "\033[33m has taken a fork\033[0m\n", philo);
		pthread_mutex_lock(philo->right_fork);
		print_philo(split_time(philo->birthday),
			philo->num, "\033[33m has taken a fork\033[0m\n", philo);
	}
}

static void	eating(t_philosophe *philo)
{
	take_forks(philo);
	philo->state = EATING;
	philo->meal_taken++;
	philo->start_eat = split_time(philo->birthday);
	print_philo(philo->start_eat, philo->num,
		"\033[32m is eating\033[0m\n", philo);
	usleep(philo->table->t_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->table->nb_meal == philo->meal_taken)
	{
		pthread_mutex_lock(&philo->table->finished_meal);
		philo->table->nb_finished_meal = philo->table->nb_finished_meal + 1;
		pthread_mutex_unlock(&philo->table->finished_meal);
	}
}

static void	sleeping(t_philosophe *philo)
{
	philo->state = SLEEPING;
	if (!philo->table->a_philo_is_dead)
		print_philo(split_time(philo->birthday),
			philo->num, "\033[34m is sleeping\033[0m\n", philo);
	usleep(philo->table->t_sleep * 1000);
}

static void	thinking(t_philosophe *philo)
{
	philo->state = THINKING;
	if (!philo->table->a_philo_is_dead)
		print_philo(split_time(philo->birthday),
			philo->num, "\033[36m is thinking\033[0m\n", philo);
}

void	*routine(void *data)
{
	t_philosophe	*philo;
	pthread_t		death_control;

	philo = (t_philosophe *)data;
	philo->start_eat = 0;
	if (pthread_create(&death_control, NULL, &control_death, philo))
	{
		printf("Error\n creating pthread\n");
		return ((void *)1);
	}
	pthread_detach(death_control);
	while (philo->state != DEAD && !philo->table->a_philo_is_dead
		&& philo->meal_taken < philo->table->nb_meal)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(T_MIN);
	}
	return ((void *) NULL);
}
