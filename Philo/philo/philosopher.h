/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:55:29 by frgojard          #+#    #+#             */
/*   Updated: 2023/04/06 16:59:56 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32;1m"
# define YELLOW  "\x1b[33;1m"
# define BLUE    "\x1b[34;1m"
# define MAGENTA "\x1b[35;1m"
# define CYAN    "\x1b[36;1m"
# define END    "\x1b[0m"

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_life
{
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	death_check;
	pthread_mutex_t	start_time_lock;
	time_t			start_time;
	time_t			*time_until_death;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				who_finished;
}			t_life;

typedef struct s_philo
{
	t_life			*life;
	int				index;
	pthread_t		philo;
	int				dinner_count;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*sec_fork;
}			t_philo;

int		philo_parsing(t_life *life, int argc, char **argv);
void	*philo_th(t_philo *philo);
time_t	get_time(void);
void	ft_usleep(int time);
void	life_clear(t_life *life);
void	philo_clear(t_life *life, pthread_t	*philo);
void	ft_print(t_philo *philo, char *str);
#endif