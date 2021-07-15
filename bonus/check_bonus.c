/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:40:37 by clorin            #+#    #+#             */
/*   Updated: 2021/07/15 11:40:43 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	invalid_arg(char *str)
{
	printf("Error\nInvalid argument : '%s'\n", str);
	return (usage(FALSE));
}

int	usage(int ret)
{
	printf("Usage : philo nb_philo t_die t_eat t_sleep [nb_eat]\n");
	printf("nb_philo: number of philosophers and forks\n");
	printf("t_die: time to die (ms)\n");
	printf("t_eat: time to eat (ms)\n");
	printf("t_sleep: time to sleep (ms)\n");
	printf("[nb_eat]: (optional) Number of time each philosophers must eat\n");
	return (ret);
}

int	valid_arg(char **argv)
{
	int	i;

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
