/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:47:17 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/25 15:18:24 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_died(char *msg, t_philo *philo, int philo_id)
{
	size_t	time_stamp;

	pthread_mutex_lock(philo->monitor_lock);
	ft_setcolor("\033[1;31m");
	time_stamp = get_current_time() - philo->start_time;
	if (!check_dead(philo))
		printf("%zu %d %s\n", time_stamp, philo_id, msg);
	ft_resetcolor();
	pthread_mutex_unlock(philo->monitor_lock);
}

void	message_routine(char *msg, t_philo *philo, int philo_id)
{
	size_t	time_stamp;

	pthread_mutex_lock(philo->monitor_lock);
	ft_setcolor("\033[0;32m");
	time_stamp = get_current_time() - philo->start_time;
	if (!check_dead(philo))
		printf("%zu %d %s\n", time_stamp, philo_id, msg);
	ft_resetcolor();
	pthread_mutex_unlock(philo->monitor_lock);
}

void	message_wrong_arg(int num)
{
	ft_setcolor("\033[1;31m");
	if (num == 1)
		printf("ERROR: invalid number_of_philosophers\n");
	else if (num == 2)
		printf("ERROR: invalid time_to_die\n");
	else if (num == 3)
		printf("ERROR: invalid time_to_eat\n");
	else if (num == 4)
		printf("ERROR: invalid time_to_sleep\n");
	else if (num == 5)
		printf("ERROR: invalid number_of_times_each_"
			"philosopher_must_eat\n");
	ft_resetcolor();
}

void	message_args(void)
{
	ft_setcolor("\033[1;31m");
	printf("\t\tRTFM! Give me 4 or 5 numbers:\n"
		"\t\t1 -> number_of_philosophers\n"
		"\t\t2 -> time_to_die\n"
		"\t\t3 -> time_to_eat\n"
		"\t\t4 -> time_to_sleep\n"
		"\t\t5 -> [number_of_times_each_philosopher_must_eat]\n"
		"\t\tf.e. ./philo 100 800 200 100 5\n");
	ft_resetcolor();
}
