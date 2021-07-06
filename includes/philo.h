/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:36:42 by clorin            #+#    #+#             */
/*   Updated: 2021/06/29 10:37:23 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>

# define FALSE 0
# define TRUE 1

typedef enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_state;

typedef struct	s_philosophe
{
	int				num;
	int				state;
//	int				t_die;
//	int				t_eat;
//	int				t_sleep;
	int				meal_taken;
//	int				*nb_finished_meal;
//	int				nb_meal;
	long			birthday;
	long			start_eat;
//	pthread_mutex_t	*printer;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_table			*table;
}				t_philosophe;

typedef struct	s_table
{
	int				nb_philo;
	int				nb_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	int				option_nb_meal;
	int				nb_finished_meal;
	int				a_philo_is_dead;
	long			start_time;
	t_philosophe	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t finished_meal;
}				t_table;

int 	ft_is_nbr(const char *str);
int		ft_atoi(const char *str);
long	split_time(long starter);
long  	get_time();
void	*routine(void *data);
void	print_philo(long ts, int num, char *msg, t_philosophe *philo);
void  ft_usleep(int duration);

#endif
