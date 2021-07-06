/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:55:30 by clorin            #+#    #+#             */
/*   Updated: 2021/07/01 18:55:48 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long  split_time(long starter)
{
    struct timeval  tv;
    long            end;

    gettimeofday(&tv, NULL);
    end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
    return (end - starter);
}

long  get_time()
{
  struct timeval  tv;
  long            end;

  gettimeofday(&tv, NULL);
  end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
    return (end); 
}

void  ft_usleep(int duration)
{
  long start;
  long current;

  start = split_time(0);
  current = start;
  while (duration > current - start)
  {
    usleep(100);
    current = split_time(0);
  }
}
