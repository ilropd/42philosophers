/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:23:37 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/25 15:36:30 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	game_over(char *msg, t_game *game, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (msg)
	{
		ft_setcolor("\033[1;31m");
		printf("%s\n", msg);
		ft_resetcolor();
	}
	pthread_mutex_destroy(&game->die_lock);
	pthread_mutex_destroy(&game->eat_lock);
	pthread_mutex_destroy(&game->monitor_lock);
	while (i < game->philos[0].counter_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	invalid_args;
	int	arg_val;

	i = 0;
	invalid_args = 0;
	while (++i < argc)
	{
		arg_val = ft_atoi(argv[i]);
		if ((arg_val <= 0) || (ft_isnum(argv[i]) == 1))
		{
			message_wrong_arg(i);
			invalid_args = 1;
		}
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
	{
		ft_setcolor("\033[1;31m");
		printf("ERROR: max safe philo amount: %d\n", PHILO_MAX);
		ft_resetcolor();
		return (1);
	}
	return (invalid_args);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if ((argc != 5) && (argc != 6))
		return (message_args(), 1);
	if (check_args(argc, argv) == 1)
		return (1);
	init_game(&game, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(&game, philos, forks, argv);
	create_philos(&game, forks);
	game_over(NULL, &game, forks);
	return (0);
}
