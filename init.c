/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:30:16 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/27 13:00:16 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_game(t_game *game, t_philo *philos)
{
	game->stop_game = 0;
	game->philos = philos;
	pthread_mutex_init(&game->die_lock, NULL);
	pthread_mutex_init(&game->eat_lock, NULL);
	pthread_mutex_init(&game->monitor_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_mutex_init(forks, NULL);
		i++;
	}
}

void	init_args(t_philo *philos, char **argv)
{
	philos->counter_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->meals_goal = ft_atoi(argv[5]);
	else
		philos->meals_goal = -1;
}

void	init_philos(t_game *game, t_philo *philos,
	pthread_mutex_t *forks, char **argv)
{
	int		i;
	size_t	time_init;

	i = 0;
	time_init = get_current_time();
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].counter_meals = 0;
		init_args(&philos[i], argv);
		philos[i].start_time = time_init;
		philos[i].last_meal = time_init;
		philos[i].stop_game = &game->stop_game;
		philos[i].die_lock = &game->die_lock;
		philos[i].eat_lock = &game->eat_lock;
		philos[i].monitor_lock = &game->monitor_lock;
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].l_fork = &forks[philos[i].counter_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}
