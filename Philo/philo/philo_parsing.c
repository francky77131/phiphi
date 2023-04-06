/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:55:52 by frgojard          #+#    #+#             */
/*   Updated: 2023/03/28 15:14:21 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (is_digit(str[i++]) == 0)
			return (0);
	return (1);
}

unsigned int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (nptr[i] == '-')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i] -48);
		i++;
	}
	return (result);
}

int	philo_parsing(t_life *life, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (is_number(argv[1]) && ft_atoi(argv[1]) > 0)
		life->nb_philo = ft_atoi(argv[1]);
	else
		return (0);
	if (is_number(argv[2]) && ft_atoi(argv[2]) > 0)
		life->time_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (is_number(argv[3]) && ft_atoi(argv[3]) > 0)
		life->time_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (is_number(argv[4]) && ft_atoi(argv[4]) > 0)
		life->time_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	life->number_of_eat = -1;
	if (argc == 6 && is_number(argv[5]) && ft_atoi(argv[5]) > 0)
		life->number_of_eat
			= ft_atoi(argv[5]);
	else if (argc == 6)
		return (0);
	return (1);
}
