/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:55:46 by frgojard          #+#    #+#             */
/*   Updated: 2023/03/30 12:02:10 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_first(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->sec_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->life->death_check);
	philo->life->time_until_death[philo->index
		- 1] = get_time() + philo->life->time_to_die;
	pthread_mutex_unlock(&philo->life->death_check);
	ft_usleep(philo->life->time_to_eat);
	philo->dinner_count++;
	pthread_mutex_lock(&philo->life->death_check);
	if (philo->dinner_count == philo->life->number_of_eat)
		philo->life->who_finished++;
	pthread_mutex_unlock(&philo->life->death_check);
	pthread_mutex_unlock(philo->sec_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	eat_sec(t_philo *philo)
{
	pthread_mutex_lock(philo->sec_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->first_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->life->death_check);
	philo->life->time_until_death[philo->index
		- 1] = get_time() + philo->life->time_to_die;
	pthread_mutex_unlock(&philo->life->death_check);
	ft_usleep(philo->life->time_to_eat);
	philo->dinner_count++;
	pthread_mutex_lock(&philo->life->death_check);
	if (philo->dinner_count == philo->life->number_of_eat)
		philo->life->who_finished++;
	pthread_mutex_unlock(&philo->life->death_check);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->sec_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->life->time_to_sleep);
}

void	think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	usleep(500);
}

void	*philo_th(t_philo *philo)
{
	if (philo->life->nb_philo == 1)
	{
		ft_print(philo, "is thinking");
		ft_print(philo, "has taken a fork");
		free(philo);
		return (NULL);
	}
	while (1)
	{
		think(philo);
		if (philo->index % 2)
			eat_first(philo);
		else
			eat_sec(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->life->death_check);
		if (philo->life->who_finished
			>= philo->life->nb_philo)
		{
			pthread_mutex_unlock(&philo->life->death_check);
			free(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->life->death_check);
	}
}
