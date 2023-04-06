/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:55:56 by frgojard          #+#    #+#             */
/*   Updated: 2023/03/28 15:11:54 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	life_clear(t_life *life)
{
	int	i;

	i = 1;
	pthread_mutex_destroy(&life->write);
	pthread_mutex_destroy(&life->death_check);
	while (i < life->nb_philo)
		pthread_mutex_destroy(&life->fork[i++]);
	free(life->time_until_death);
	free(life->fork);
	free(life);
}

void	philo_clear(t_life *life, pthread_t *philo)
{
	int	i;

	i = 0;
	while (i < life->nb_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	free(&philo[0]);
	free(&life->philo[0]);
	return ;
	philo = NULL;
}
