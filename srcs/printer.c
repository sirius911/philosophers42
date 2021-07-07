/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:39:03 by clorin            #+#    #+#             */
/*   Updated: 2021/07/02 14:39:21 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_len_nbr(long n)
{
	unsigned int	size;

	size = 1;
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(long n)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = ft_len_nbr(n);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > i)
	{
		size--;
		str[size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void	print_philo(long ts, int num, char *msg, t_philosophe *philo)
{
	char		str[100];
	char		*str_ts;
	char		*str_num;
	int			i;
	int			j;

	if (philo->state != DEAD && !philo->table->a_philo_is_dead)
	{
		i = 0;
		str_num = ft_itoa(num);
		str_ts = ft_itoa(ts);
		j = 0;
		while (str_ts[j])
			str[i++] = str_ts[j++];
		str[i++] = ' ';
		j = 0;
		while (str_num[j])
			str[i++] = str_num[j++];
		j = 0;
		while (msg[j])
			str[i++] = msg[j++];
		str[i] = '\0';
		pthread_mutex_lock(&philo->table->printer);
		if (!philo->table->a_philo_is_dead)
			write (1, str, i);
		pthread_mutex_unlock(&philo->table->printer);
		free (str_num);
		free (str_ts);
	}
}