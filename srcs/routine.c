/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:48:36 by clorin            #+#    #+#             */
/*   Updated: 2021/07/01 18:49:09 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void eating(t_philosophe *philo)
{
    philo->state = EATING;
    philo->meal_taken++;
    philo->start_eat = split_time(philo->birthday);
    printf("%ld %d is eating\n", philo->start_eat, philo->num);
    usleep(philo->t_eat * 1000);
    if (philo->nb_meal == philo->meal_taken)
        *philo->nb_finished_meal = *philo->nb_finished_meal + 1;
}

static void sleeping(t_philosophe *philo)
{
    philo->state = SLEEPING;
    
    printf("%ld %d is sleeping\n", split_time(philo->birthday), philo->num);
    usleep(philo->t_sleep * 1000);
}

static void thinking(t_philosophe *philo)
{
    philo->state = THINKING;
    
    printf("%ld %d is thinking\n", split_time(philo->birthday), philo->num);
}

void  *routine(void *data)
{
  t_philosophe  *philo;

  philo = (t_philosophe *)data;
  philo->birthday = get_time();
  philo->start_eat = 0;
  while (philo->meal_taken < philo->nb_meal && philo->state != DEAD)
  {
    eating(philo);
    sleeping(philo);
    thinking(philo);
  }
  return ((void*)NULL);
}
