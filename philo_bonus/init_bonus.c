/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:01:13 by marvin            #+#    #+#             */
/*   Updated: 2024/08/15 20:06:14 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_databank(t_databank *data, char **argv, int argc)
{
	data->num_of_phils = ft_atoi(argv[1]);
	data->deathdelay = ft_atoi(argv[2]);
	data->eatdelay = ft_atoi(argv[3]);
	data->sleepdelay = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	data->sated_counter = 0;
	sem_unlink("/lock_counter");
	sem_unlink("/philo_eating");
	sem_unlink("/exit_process");
	sem_unlink("/philo_messaging");
	data->exit_process = sem_open("/exit_process", O_CREAT | O_EXCL, 0666, 0);
	data->lock_eating = sem_open("/philo_eating", O_CREAT | O_EXCL, 0666, 1);
	data->lock_messaging = sem_open("/philo_messaging", O_CREAT | O_EXCL, 0666,
			1);
	data->lock_counter = sem_open("/lock_counter", O_CREAT | O_EXCL, 0666, 0);
	if (data->exit_process == SEM_FAILED || data->lock_eating == SEM_FAILED
		|| data->lock_messaging == SEM_FAILED
		|| data->lock_counter == SEM_FAILED)
		return (1);
	return (0);
}

sem_t	*open_sesame(int amount_philos)
{
	sem_t	*forks;

	sem_unlink("/philo_forks");
	forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0666, amount_philos);
	if (forks == SEM_FAILED)
	{
		forks = sem_open("/philo_forks", 0);
		if (forks == SEM_FAILED)
		{
			printf("error in sem_open");
			return (NULL);
		}
	}
	return (forks);
}

void	init_philo(t_philo *philos, int id)
{
	philos->ident = id + 1;
	philos->food_consumed = 0;
	philos->sated = 0;
	philos->confirmed_death = 0;
	philos->timestamp_last_meal = timer_start();
}

void	init_process(t_philo *philos, sem_t *forks)
{
	int	i;

	i = -1;
	while (++i < philos->databank->num_of_phils)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			printf("fork error");
			cleanup_func(philos, forks);
			return ;
		}
		else if (philos[i].pid == 0)
			philo_routine(&philos[i], forks);
	}
	while (philos->databank->max_meals != -1)
	{
		if (philos->databank->sated_counter >= philos->databank->num_of_phils)
			break ;
		sem_wait(philos->databank->lock_counter);
		philos->databank->sated_counter += 1;
	}
	sem_wait(philos->databank->exit_process);
	cleanup_func(philos, forks);
}

int	init_program(t_philo *philos, t_databank *data)
{
	int		i;
	sem_t	*forks;

	i = -1;
	data->init_time = timer_start();
	forks = open_sesame(data->num_of_phils);
	if (forks == NULL)
	{
		cleanup_func(philos, forks);
		return (1);
	}
	while (++i < data->num_of_phils)
	{
		philos[i].databank = data;
		init_philo(&philos[i], i);
	}
	init_process(philos, forks);
	return (0);
}
