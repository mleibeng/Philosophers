/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:01:13 by marvin            #+#    #+#             */
/*   Updated: 2024/03/06 21:59:06 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_databank(t_databank *databank, char **argv, int argc)
{
	databank->num_of_phils = ft_atoi(argv[1]);
	databank->deathdelay = ft_atoi(argv[2]);
	databank->eatdelay = ft_atoi(argv[3]);
	databank->sleepdelay = ft_atoi(argv[4]);
	if (argc == 6)
		databank->max_meals = ft_atoi(argv[5]);
	else
		databank->max_meals = -1;
	databank->sated_counter = 0;
}

int	init_mutex(pthread_mutex_t *forks, t_discussion *program, int amount_philo)
{
	int	i;

	i = -1;
	program->death_flag = 0;
	if (pthread_mutex_init(&program->lock_messaging, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->lock_eating, NULL) != 0)
		return (1);
	while (++i < amount_philo)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
	return (0);
}

void	init_philo(t_philo *philos, int id, t_discussion *program,
		pthread_mutex_t *forks)
{
	philos->tid = id + 1;
	philos->food_consumed = 0;
	philos->sated = 0;
	if (philos->databank->num_of_phils > 1)
	{
		philos->right_f = &forks[(id + 1) % program->philos[0].databank->num_of_phils];
	}
	philos->left_f = &forks[id];
	philos->confirmed_death = &program->death_flag;
	philos->lock_messaging = &program->lock_messaging;
	philos->lock_eating = &program->lock_eating;
	philos->timestamp_last_meal = timer_start();
}

int	init_threads(t_discussion *program, pthread_t *watchguard)
{
	int	i;

	if (pthread_create(watchguard, NULL, &guard_routine, &program->philos) != 0)
	{
		cleanup_func(program, program->philos->databank, watchguard, 0);
		return (1);
	}
	i = -1;
	while (++i < program->philos->databank->num_of_phils)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
		{
			cleanup_func(program, program->philos->databank, watchguard, 1);
			return (1);
		}
		usleep(50);
	}
	return (0);
}

int	init_program(t_discussion *program, t_databank *data)
{
	int				i;
	t_philo			*philos;
	pthread_t		watchguard;
	pthread_mutex_t	forks[MAX_PHILO];

	i = -1;
	if (init_mutex(forks, program, data->num_of_phils) != 0)
	{
		cleanup_func(program, data, NULL, 0);
		return (1);
	}
	while (++i < data->num_of_phils)
	{
		philos = &program->philos[i];
		philos->databank = data;
		data->init_time = timer_start();
		init_philo(philos, i, program, forks);
	}
	if (init_threads(program, &watchguard))
		return (1);
	cleanup_func(program, data, &watchguard, 2);
	return (0);
}
