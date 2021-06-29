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

int increment(int i) {
  return i+1;
}

void *func(void * param) {
  int err;
  (void) param;
  for(int j=0;j<1000000;j++) {
    err=pthread_mutex_lock(&mutex_global);
    if(err!=0)
      printf("pthread_mutex_lock error = %d\t", err);
    global=increment(global);
    err=pthread_mutex_unlock(&mutex_global);
    if(err!=0)
    	printf("pthread_mutex_unlock error = %d\t", err);
  }
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t thread[NTHREADS];
  int err;
  (void)argc;
  (void)argv;

  err=pthread_mutex_init( &mutex_global, NULL);
  if(err!=0)
  	printf("pthread_mutex_init error = %d\t", err);

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(thread[i]),NULL,&func,NULL);
    if(err!=0)
    	printf("pthread_create error = %d\t", err);
  }
  for(int i=0; i<1000000000;i++) { /*...*/ }

  for(int i=NTHREADS-1;i>=0;i--) {
    err=pthread_join(thread[i],NULL);
    if(err!=0)
    	printf("pthread_join error = %d\t", err);
  }

  err=pthread_mutex_destroy(&mutex_global);
  if(err!=0)
  	printf("pthread_mutex_destroy error = %d\t", err);

  printf("global: %ld\n",global);

  return(0);
}
