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

static void *control_death(void *data)
{
    t_philosophe *philo;
    long ts;

    philo = (t_philosophe *)data;
    if (philo->table->option_nb_meal)
    {
        while (philo->table->nb_meal > 0 && philo->meal_taken < philo->table->nb_meal
        && philo->state != DEAD)
        {
         ts = split_time(philo->birthday);
            if ((philo->table->t_die < ts - philo->start_eat)
                && philo->state != EATING)
            {
             print_philo(ts, philo->num, " died\n", philo);
             philo->state = DEAD;
             philo->table->a_philo_is_dead = TRUE;
             break ;
            }
            usleep(100);
        }
    }
    else
    {
        while (philo->state != DEAD && !philo->table->a_philo_is_dead)
        {
         ts = split_time(philo->birthday);
            if ((philo->table->t_die < ts - philo->start_eat)
                && philo->state != EATING)
            {
             print_philo(ts, philo->num, " died\n", philo);
             philo->state = DEAD;
             philo->table->a_philo_is_dead = TRUE;
             break ;
            }
            usleep(100);
        }
    }
    return (NULL);
}

static void take_forks(t_philosophe *philo)
{
    if (philo->num % 2)
    {
        pthread_mutex_lock(philo->right_fork);
        print_philo(split_time(philo->birthday), philo->num, " has taken a fork\n", philo);
        pthread_mutex_lock(philo->left_fork);
        print_philo(split_time(philo->birthday), philo->num, " has taken a fork\n", philo);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_philo(split_time(philo->birthday), philo->num, " has taken a fork\n", philo);
        pthread_mutex_lock(philo->right_fork);
        print_philo(split_time(philo->birthday), philo->num, " has taken a fork\n", philo);
    }    
}

static void eating(t_philosophe *philo)
{
    take_forks(philo);
    philo->state = EATING;
    philo->meal_taken++;
    philo->start_eat = split_time(philo->birthday);
    print_philo(philo->start_eat, philo->num, "\033[32m is eating\033[0m\n", philo);
    usleep(philo->table->t_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    if (philo->table->option_nb_meal && philo->table->nb_meal == philo->meal_taken)
    {
        pthread_mutex_lock(&philo->table->finished_meal);
/*        print_philo(philo->start_eat, philo->num, " a fini son repas\n", philo);*/
        philo->table->nb_finished_meal = philo->table->nb_finished_meal + 1;
        pthread_mutex_unlock(&philo->table->finished_meal);
    }
}

static void sleeping(t_philosophe *philo)
{
    philo->state = SLEEPING;
    print_philo(split_time(philo->birthday), philo->num, " is sleeping\n", philo);
    usleep(philo->table->t_sleep * 1000);
}

static void thinking(t_philosophe *philo)
{
    philo->state = THINKING;
    print_philo(split_time(philo->birthday), philo->num, " is thinking\n", philo);
}



void  *routine(void *data)
{
  t_philosophe  *philo;
  pthread_t     death_control;

  philo = (t_philosophe *)data;
  philo->birthday = get_time();
  philo->start_eat = 0;
  pthread_create(&death_control, NULL, &control_death, philo);
  // todo gestion erreur de pthread_create
  pthread_detach(death_control);
  if (philo->table->option_nb_meal)
  {
    while (philo->state != DEAD && !philo->table->a_philo_is_dead  && philo->meal_taken < philo->table->nb_meal)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
        usleep(100);
    }

    }
    else
    {
        while (philo->state != DEAD && !philo->table->a_philo_is_dead)
        {
          eating(philo);
          sleeping(philo);
          thinking(philo);
          usleep(100);
        }    
    }
  return ((void*)NULL);
}
