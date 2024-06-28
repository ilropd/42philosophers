/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:18:16 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/25 15:01:28 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->die_lock);
	if (*philo->stop_game == 1)
	{
		pthread_mutex_unlock(philo->die_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->die_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		convert_time(1);
	while (!check_dead(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (arg);
}

int	create_philos(t_game *game, pthread_mutex_t *forks)
{
	pthread_t	god;
	int			i;

	i = 0;
	if (pthread_create(&god, NULL, &status, game->philos) != 0)
		game_over("ERROR: god_threads failed\n", game, forks);
	while (i < game->philos[0].counter_philos)
	{
		if (pthread_create(&game->philos[i].thread,
				NULL, &routine, &game->philos[i]) != 0)
			game_over("ERROR: philos_threads failed\n", game, forks);
		i++;
	}
	i = 0;
	if (pthread_join(god, NULL) != 0)
		game_over("ERROR: god_join failed\n", game, forks);
	while (i < game->philos[0].counter_philos)
	{
		if (pthread_join(game->philos[i].thread, NULL) != 0)
			game_over("ERROR: philos_join failed\n", game, forks);
		i++;
	}
	return (0);
}
