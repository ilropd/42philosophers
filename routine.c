/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:40:59 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/26 15:17:57 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	message_routine("is thinking", philo, philo->id);
}

void	ft_sleep(t_philo *philo)
{
	message_routine("is sleeping", philo, philo->id);
	convert_time(philo->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	message_routine("has taken a fork", philo, philo->id);
	if (philo->counter_philos == 1)
	{
		convert_time(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	message_routine("has taken a fork", philo, philo->id);
	philo->eating = 1;
	message_routine("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_current_time();
	philo->counter_meals += 1;
	pthread_mutex_unlock(philo->eat_lock);
	convert_time(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
