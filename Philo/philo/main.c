/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:56:14 by frgojard          #+#    #+#             */
/*   Updated: 2023/04/06 17:03:37 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_init(t_life *life, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	life->time_until_death[i - 1]
		= life->start_time + life->time_to_die;
	philo->index = i;
	philo->dinner_count = 0;
	philo->first_fork = &life->fork[i - 1];
	if (i == life->nb_philo)
		philo->sec_fork = &life->fork[0];
	else
		philo->sec_fork = &life->fork[i];
	philo->life = life;
	life->philo[i - 1] = *philo;
	return (philo);
}

int	life_init(t_life *life)
{
	int			i;

	i = 0;
	life->philo = malloc(sizeof (t_philo) * life->nb_philo);
	if (!life->philo)
		return (0);
	life->fork = malloc(sizeof (pthread_mutex_t) * life->nb_philo);
	if (!life->fork)
		return (0);
	life->time_until_death = malloc(sizeof(time_t) * life->nb_philo);
	if (!life->time_until_death)
		return (0);
	while (i < life->nb_philo)
		pthread_mutex_init(&life->fork[i++], NULL);
	pthread_mutex_init(&life->write, NULL);
	pthread_mutex_init(&life->start_time_lock, NULL);
	pthread_mutex_init(&life->death_check, NULL);
	life->who_finished = 0;
	life->start_time = get_time();
	return (1);
}

pthread_t	*philo_launch(t_life *life)
{
	pthread_t	*philo;
	int			i;

	i = 1;
	philo = malloc(sizeof(pthread_t) * life->nb_philo);
	if (!philo)
		return ((void *) NULL);
	while (i <= life->nb_philo)
	{
		if (pthread_create(philo + (i - 1), NULL, (void *)philo_th,
				philo_init(life, i)))
			return ((void *) NULL);
		i += 2;
	}
	i = 2;
	ft_usleep(5);
	while (i <= life->nb_philo)
	{
		if (pthread_create(philo + (i - 1), NULL, (void *)philo_th,
				philo_init(life, i)))
			return ((void *) NULL);
		i += 2;
	}
	return (philo);
}

void	death_cycle(t_life *life, int i)
{
	usleep (1000);
	while (1)
	{
		if (i == life->nb_philo)
			i = 0;
		pthread_mutex_lock(&life->death_check);
		if (life->time_until_death[i] <= get_time())
		{
			life->who_finished = life->nb_philo;
			pthread_mutex_unlock(&life->death_check);
			usleep(10);
			pthread_mutex_lock(&life->start_time_lock);
			printf("%ld %d died\n", get_time() - life->start_time, i + 1);
			pthread_mutex_unlock(&life->start_time_lock);
			return ;
		}
		if (life->who_finished == life->nb_philo)
		{
			life->who_finished = life->nb_philo;
			pthread_mutex_unlock(&life->death_check);
			usleep(10);
			return ;
		}
		pthread_mutex_unlock(&life->death_check);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_life		*life;
	pthread_t	*philo;

	life = malloc(sizeof(t_life));
	if (!life)
		return (0);
	if (philo_parsing(life, argc, argv) == 0)
	{
		printf(RED"Error\n"END);
		free(life);
		return (0);
	}
	if (life_init(life) == 1)
	{
		philo = philo_launch(life);
		if (philo)
			death_cycle(life, 0);
		philo_clear(life, philo);
	}
	life_clear(life);
	return (1);
}
