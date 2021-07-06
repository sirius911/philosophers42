/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:35:52 by clorin            #+#    #+#             */
/*   Updated: 2021/06/29 10:36:30 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int invalid_arg(char *str)
{
  printf("Error\nInvalid argument : '%s'\n", str);
  return (FALSE);
}

int valid_arg(char **argv)
{
  int i;

  i = 1;
  while (argv[i])
  {
    if (!ft_is_nbr(argv[i]))
      return (invalid_arg(argv[i]));
    if (argv[i][0] == '0' || argv[i][0] == '-')
      return (invalid_arg(argv[i]));
    i++;
  }
  return (TRUE);
}

void  free_philo(t_table *table)
{
  if (table->philo)
    free(table->philo);
}

void  free_forks(t_table *table)
{
  if (table->forks)
    free(table->forks);
}

int  free_mutex(t_table *table)
{
  int i;

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

int init_table(t_table *table, char **argv, int limit_nb_eat)
{
  table->nb_philo = ft_atoi(argv[1]);
  table->nb_forks = table->nb_philo;
  table->t_die = ft_atoi(argv[2]);
  table->t_eat = ft_atoi(argv[3]);
  table->t_sleep = ft_atoi(argv[4]);
  table->option_nb_meal = limit_nb_eat;
  if (limit_nb_eat)
    table->nb_meal = ft_atoi(argv[5]);
  else
    table->nb_meal = 0;
  table->nb_finished_meal = 0;
  table->a_philo_is_dead = FALSE;
  table->philo = NULL;
  table->forks = NULL;
  
  // malloc
  table->philo = (t_philosophe *) malloc(sizeof(t_philosophe) * table->nb_philo);
  if (!table->philo)
    return (FALSE);
  table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nb_forks);
  if (!table->forks)
  {
    free_philo(table);
    return (FALSE);
  }
  // init philosphers
  
  int i = 0;
  while (i < table->nb_philo)
  {
    table->philo[i].num = i + 1;
    table->philo[i].table = table;
    table->philo[i].meal_taken = 0;
    table->philo[i].state = THINKING;
    table->philo[i].left_fork = &table->forks[i];
    if (i == 0)
      table->philo[i].right_fork = &table->forks[table->nb_philo - 1];
    else
      table->philo[i].right_fork = &table->forks[i - 1];
    i++;
  }
  //init forks
  
  if (pthread_mutex_init(&table->finished_meal, NULL) != 0)
    {
      printf("Error\nInit mutex error\n");
      return (free_mutex(table));
    }

  i = 0;
  while (i < table->nb_forks)
  {
    if (pthread_mutex_init(&table->forks[i], NULL) != 0)
    {
      printf("Error\nInit mutex error\n");
      return (free_mutex(table));
    }
    i++;
  }

  if (pthread_mutex_init(&table->printer, NULL) != 0)
  {
    printf("Error\nInit mutex error\n");
    return (free_mutex(table));
  }
  return (TRUE);
}

int run_philo(t_table *table)
{
  int   i;
  pthread_t thread;
  t_philosophe *philosophe;

  i = 0;
  table->start_time = get_time();
  while (i < table->nb_philo)
  {
    philosophe = &table->philo[i];
    philosophe->birthday = table->start_time;
    pthread_create(&thread, NULL, &routine, (void *)philosophe);
    // TODO Controle
    pthread_detach(thread);
    i++;
  }
  return (TRUE);
}

void ending_philo(t_table *table)
{
  int i;

  i = 0;
  while (i < table->nb_philo)
  {
    //print_philo(split_time(table->philo[i].birthday), table->philo[i].num, etat(table->philo[i].state), table->printer);
    *(&table->philo[i].state) = DEAD;
    i++;
  }
}

void  loop_death(t_table *table)
{
  while (!table->a_philo_is_dead)
  {
   usleep(500);
  }
  ending_philo(table);
}

void  loop_nb_meal(t_table *table)
{
  int   dead;

  dead = FALSE;
  while (!table->a_philo_is_dead
    && table->nb_finished_meal < table->nb_philo)
    {
      usleep(500);
    }
  dead = table->a_philo_is_dead;
  table->a_philo_is_dead = TRUE;
  ending_philo(table);
  if (table->nb_finished_meal == table->nb_philo && !dead)
      printf("All philosophers ate %d meal(s) !\n", table->nb_meal);
}

int main ( int argc, char **argv)
{
  t_table table;
  long  start;
  start = split_time(0);
  if (argc >= 5 && argc <= 6)
  {
    if (!valid_arg(argv))
      return (EXIT_FAILURE);
    if (!init_table(&table, argv, argc == 6))
      return (EXIT_FAILURE);
    run_philo(&table);
    if (table.nb_meal > 0)
      loop_nb_meal(&table);
    else
      loop_death(&table);
   //sleep(2);
    free_philo(&table);
    free_mutex(&table);
    free_forks(&table);
  }
  else
  {
    printf("Error.\nInvalid number of arguments :\n");
    printf("Usage : philo nb_philo t_die t_eat t_sleep [nb_eat]\n");
    printf("nb_philo: number of philosophers and forks\n");
    printf("t_die: time to die (ms)\n");
    printf("t_eat: time to eat (ms)\n");
    printf("t_sleep: time to sleep (ms)\n");
    printf("[nb_eat]: (optional) Number of time each philosophers must eat\n");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}