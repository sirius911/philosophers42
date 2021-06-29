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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define PHILOSOPHES 3

pthread_t phil[PHILOSOPHES];
pthread_mutex_t baguette[PHILOSOPHES];

void mange(int id) {
  printf("Philosophe [%d] mange ",id);
usleep(500);
  printf("\n");
}

void* philosophe ( void* arg )
{
  int *id=(int *) arg;
  int left = *id;
  int right = (left + 1) % PHILOSOPHES;
  while(true) {
    // philosophe pense
    printf("Philosophe [%d] ", *id);
    if(left<right) {
      printf("prend left[%d] ", left);
      pthread_mutex_lock(&baguette[left]);
      printf("ok\n");
      printf("prend right[%d] ", right);
      pthread_mutex_lock(&baguette[right]);
      printf("ok\n");
    }
    else {
      printf("prend right[%d] ", right);
      pthread_mutex_lock(&baguette[right]);
      printf("ok\n");
      printf("prend left[%d] ", left);
      pthread_mutex_lock(&baguette[left]);
      printf("ok\n");
    }
    mange(*id);
    printf("libere left[%d]\n", left);
    pthread_mutex_unlock(&baguette[left]);
    printf("libere right[%d]\n", right);
    pthread_mutex_unlock(&baguette[right]);
  }
  return (NULL);
}

int main ( int argc, char *argv[])
{
  (void) argc;
  (void) argv;
   long i;
   int id[PHILOSOPHES];

   srand(getpid());

   for (i = 0; i < PHILOSOPHES; i++)
   {
      id[i]=i;
      printf("id[%ld]=%d\n", i, id[i]);
   }

   for (i = 0; i < PHILOSOPHES; i++)
   {
      pthread_mutex_init( &baguette[i], NULL);
      printf("mutex_init(%ld)\n", i);
   }

   for (i = 0; i < PHILOSOPHES; i++)
   {
     pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );
      printf("pthread_create(%ld)\n", i);
   }

   for (i = 0; i < PHILOSOPHES; i++)
      pthread_join(phil[i], NULL);

   return (EXIT_SUCCESS);
}