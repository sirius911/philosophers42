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

int  free_mutex(t_table *table)
{
  int i;

  pthread_mutex_unlock(&table->printer);
  pthread_mutex_destroy(&table->printer);
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
  if (limit_nb_eat)
    table->nb_meal = ft_atoi(argv[5]);
  else
    table->nb_meal = 0;
  table->nb_finished_meal = 0;
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
    table->philo[i].t_die = table->t_die;
    table->philo[i].t_eat = table->t_eat;
    table->philo[i].t_sleep = table->t_sleep;
    table->philo[i].nb_meal = table->nb_meal;
    table->philo[i].meal_taken = 0;
    table->philo[i].nb_finished_meal = &table->nb_finished_meal;
    table->philo[i].state = THINKING;
    table->philo[i].printer = &table->printer;
    table->philo[i].left_fork = &table->forks[i];
    // si 1 seul philosophe ?
    if (i == 0)
      table->philo[i].right_fork = &table->forks[table->nb_philo - 1];
    else
      table->philo[i].right_fork = &table->forks[i - 1];
    i++;
  }
  //init forks
  
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
  while (i < table->nb_philo)
  {
    philosophe = &table->philo[i];
    //printf("pthread_create(philo[%d]...", philosophe->num);
    pthread_create(&thread, NULL, &routine, (void *)philosophe);
    //printf("ok\n");
    // TODO Controle
    pthread_detach(thread);
    i++;
  }
  return (TRUE);
}

int main ( int argc, char **argv)
{
  t_table table;
  long  start;
  start = split_time(0);
  printf("time = %ld\n", start);
  if (argc >= 5 && argc <= 6)
  {
    if (!valid_arg(argv))
      return (EXIT_FAILURE);
    if (!init_table(&table, argv, argc == 6))
      return (EXIT_FAILURE);
    printf("init table ... ok\n");
    printf("%d philosopher(s) with %d forks\n", table.nb_philo, table.nb_forks);
    printf("time to die = %d ms, time to eat = %d ms, time to sleep = %d ms, nb meal = %d \n", table.t_die, table.t_eat, table.t_sleep, table.nb_meal);
    for (int i = 0; i < table.nb_philo; i++)
      printf("philo[%d], right = %p left = %p\n", table.philo[i].num, table.philo[i].right_fork, table.philo[i].left_fork);
    run_philo(&table);
    while (table.nb_finished_meal < table.nb_philo)
        ;
    printf("free_philo...");
    free_philo(&table);
    free_mutex(&table);
    free(table.forks);
    printf("ok\n");
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
  usleep(500);
  printf("time = %ld ms\n", split_time(start));
  return (EXIT_SUCCESS);
}