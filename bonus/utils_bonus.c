/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:42:58 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 11:43:00 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_isspace(int ch)
{
	if (ch == '\t' || ch == '\n' || ch == '\v'
		|| ch == '\f' || ch == '\r' || ch == ' ')
		return (TRUE);
	else
		return (FALSE);
}

static int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_is_nbr(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		else
			break ;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_atoi(const char *str)
{
	long		result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		result = (result * 10) + str[i++] - '0';
	result = ((int)(sign * result));
	return (result);
}
