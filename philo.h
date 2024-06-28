/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:25:12 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/27 12:59:52 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				counter_meals;
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_goal;
	int				counter_philos;
	int				*stop_game;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*die_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*monitor_lock;
}	t_philo;

typedef struct s_game
{
	int				stop_game;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	monitor_lock;
	t_philo			*philos;
}	t_game;

/* main.c */
void	game_over(char *msg, t_game *game, pthread_mutex_t *forks);
int		check_args(int argc, char **argv);

/* colors.c */
void	ft_setcolor(const char *color_code);
void	ft_resetcolor(void);

/* init.c */
void	init_game(t_game *game, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philos);
void	init_philos(t_game *game, t_philo *philos,
			pthread_mutex_t *forks, char **argv);
void	init_args(t_philo *philos, char **argv);

/* message.c */
void	message_died(char *msg, t_philo *philo, int philo_id);
void	message_routine(char *msg, t_philo *philo, int philo_id);
void	message_wrong_arg(int num);
void	message_args(void);

/* philo.c */
int		check_dead(t_philo *philo);
void	*routine(void *arg);
int		create_philos(t_game *game, pthread_mutex_t *forks);

/* routine.c */
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);

/* status */
int		philo_dead(t_philo *philo, size_t ttd);
int		check_deadman(t_philo *philos);
int		check_meals_goals(t_philo *philos);
void	*status(void *arg);

/* utils.c */
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_isnum(char *str);
void	convert_time(size_t goal_milliseconds);
size_t	get_current_time(void);

#endif
