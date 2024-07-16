/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:27:25 by mleibeng          #+#    #+#             */
/*   Updated: 2024/01/28 16:44:01 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	rest_routine(t_philo *philos)
{
	print_function(philos, "is sleeping\n");
	improved_sleep(philos->databank->sleepdelay);
	print_function(philos, "is thinking\n");
}

void	eating_routine(t_philo *philos, sem_t *forks)
{
	sem_wait(forks);
	print_function(philos, "has taken a fork\n");
	sem_wait(forks);
	print_function(philos, "has taken a fork\n");
	sem_wait(philos->databank->lock_eating);
	print_function(philos, "is eating\n");
	philos->timestamp_last_meal = timer_start();
	philos->food_consumed += 1;
	sem_post(philos->databank->lock_eating);
	improved_sleep(philos->databank->eatdelay);
	if (philos->food_consumed >= philos->databank->max_meals
		&& philos->databank->max_meals != -1 && philos->sated != 1)
	{
		philos->sated = 1;
		sem_post(philos->databank->lock_counter);
	}
	sem_post(forks);
	sem_post(forks);
}

void	philo_routine(t_philo *philos, sem_t *forks)
{
	pthread_t	check_condition;
	int			i;

	i = -1;
	pthread_create(&check_condition, NULL, check_death_flag, philos);
	pthread_detach(check_condition);
	while (1)
	{
		eating_routine(philos, forks);
		rest_routine(philos);
	}
	exit(EXIT_SUCCESS);
}
