/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:27:25 by mleibeng          #+#    #+#             */
/*   Updated: 2024/08/26 11:46:54 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	rest_routine(t_philo *philo, size_t current_time)
{
	if (!*(philo->confirmed_death))
		print_function(philo, "is sleeping\n", current_time);
	improved_sleep(philo->databank->sleepdelay, philo);
	if (check_death_flag(philo))
		return ;
	if (!*(philo->confirmed_death))
		print_function(philo, "is thinking\n", current_time);
}

void	eating_routine(t_philo *philo, size_t current_time)
{
	pthread_mutex_lock(philo->left_f);
	if (!*(philo->confirmed_death))
		print_function(philo, "has taken a fork\n", current_time);
	pthread_mutex_lock(philo->right_f);
	if (!*(philo->confirmed_death))
		print_function(philo, "has taken a fork\n", current_time);
	pthread_mutex_lock(philo->lock_eating);
	if (!*(philo->confirmed_death))
		print_function(philo, "is eating\n", current_time);
	philo->timestamp_last_meal = timer_start();
	philo->food_consumed += 1;
	pthread_mutex_unlock(philo->lock_eating);
	improved_sleep(philo->databank->eatdelay, philo);
	pthread_mutex_lock(philo->lock_eating);
	if (philo->food_consumed >= philo->databank->max_meals && !philo->sated)
	{
		philo->sated = 1;
		philo->databank->sated_counter++;
	}
	pthread_mutex_unlock(philo->lock_eating);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

void	lonely_philo(t_philo *philo)
{
	while (!check_death_flag(philo))
	{
		pthread_mutex_lock(philo->left_f);
		if (!*(philo->confirmed_death))
			print_function(philo, "has taken a fork\n", timer_start());
		improved_sleep(philo->databank->deathdelay, philo);
		pthread_mutex_unlock(philo->left_f);
	}
}

void	*philo_routine(void *philos)
{
	t_philo	*routine_philo;
	t_timer	current_time;

	routine_philo = (t_philo *)philos;
	if (routine_philo->databank->num_of_phils == 1)
	{
		lonely_philo(routine_philo);
		return (philos);
	}
	while (1)
	{
		current_time.start_time = timer_start();
		eating_routine(routine_philo, current_time.start_time);
		if (check_death_flag(routine_philo))
			break ;
		rest_routine(routine_philo, current_time.start_time);
		if (check_death_flag(routine_philo))
			break ;
	}
	return (philos);
}

void	*guard_routine(void *all_philos)
{
	t_philo	*watchguard;

	watchguard = (t_philo *)all_philos;
	while (!*(watchguard->confirmed_death))
	{
		pthread_mutex_lock(watchguard->lock_eating);
		if (watchguard->databank->sated_counter
			>= watchguard->databank->num_of_phils
			&& watchguard->databank->max_meals > 0)
		{
			*(watchguard->confirmed_death) = 1;
			pthread_mutex_unlock(watchguard->lock_eating);
			break ;
		}
		pthread_mutex_unlock(watchguard->lock_eating);
		if (check_starvation(watchguard))
			break ;
	}
	return (NULL);
}
