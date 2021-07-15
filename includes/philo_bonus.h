/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:31:22 by clorin            #+#    #+#             */
/*   Updated: 2021/07/09 12:31:24 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FALSE 0
# define TRUE 1
# define T_MIN 100

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_state;

typedef struct s_philosophe
{
	int				num;
	int				state;
	int				meal_taken;
	long			birthday;
	long			start_eat;
	//pthread_mutex_t	*left_fork;
	//pthread_mutex_t	*right_fork;
	struct s_table	*table;
}				t_philosophe;

typedef struct s_table
{
	int				nb_philo;
	int				nb_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	int				nb_finished_meal;
	int				a_philo_is_dead;
	long			start_time;
	t_philosophe	*philo;
	//pthread_mutex_t	*forks;
	t_pid			*philo_pid;
	pthread_mutex_t	printer;
	pthread_mutex_t	finished_flag;
}				t_table;

int		ft_is_nbr(const char *str);
int		ft_atoi(const char *str);
long	split_time(long starter);
long	get_time(void);
void	*routine(void *data);
void	print_philo(long ts, int num, char *msg, t_philosophe *philo);
void	ft_usleep(int duration);
void	*control_death(void *data);
void	free_philo(t_table *table);
void	free_forks(t_table *table);
int		free_mutex(t_table *table);
int		delete_table(t_table *table);
int		valid_arg(char **argv);
int		usage(int ret);
int		init_table(t_table *table, char **argv, int limit_nb_eat);

#endif
