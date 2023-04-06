/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:55:38 by frgojard          #+#    #+#             */
/*   Updated: 2023/04/06 17:03:30 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time)
{
	usleep(time * 1000);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->life->write);
	pthread_mutex_lock(&philo->life->death_check);
	if (philo->life->who_finished != philo->life->nb_philo)
	{
		pthread_mutex_lock(&philo->life->start_time_lock);
		printf(GREEN"%ld "END, get_time() - philo->life->start_time);
		pthread_mutex_unlock(&philo->life->start_time_lock);
		printf(CYAN"%d "END, philo->index);
		printf(MAGENTA"%s\n"END, str);
	}
	pthread_mutex_unlock(&philo->life->death_check);
	pthread_mutex_unlock(&philo->life->write);
}
