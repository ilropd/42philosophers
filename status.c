/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:31:07 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/26 16:11:33 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t ttd)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_current_time() - philo->last_meal >= ttd
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	check_deadman(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].counter_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			message_died("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].die_lock);
			*philos->stop_game = 1;
			pthread_mutex_unlock(philos[0].die_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meals_goals(t_philo *philos)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (philos[0].meals_goal == -1)
		return (0);
	while (i < philos[0].counter_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].counter_meals >= philos[i].meals_goal)
			counter++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (counter == philos[0].counter_philos)
	{
		pthread_mutex_lock(philos[0].die_lock);
		*philos->stop_game = 1;
		pthread_mutex_unlock(philos[0].die_lock);
		return (1);
	}
	return (0);
}

void	*status(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
		if ((check_deadman(philos) == 1) || (check_meals_goals(philos) == 1))
			break ;
	return (arg);
}
