/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:38:58 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 13:38:59 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

static void	ft_print(char *str_ts, char *str_num, char *msg,
	t_philosophe *philo)
{
	char	str[100];
	int		i;
	int		j;

	j = 0;
	i = 0;
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
	sem_wait(philo->table->printer);
	write (1, str, i);
}

void	print_philo(long ts, int num, char *msg, t_philosophe *philo)
{
	char		*str_ts;
	char		*str_num;

	if (philo->state != DEAD)
	{
		str_num = ft_itoa(num);
		str_ts = ft_itoa(ts);
		ft_print(str_ts, str_num, msg, philo);
		free (str_num);
		free (str_ts);
	}
}
