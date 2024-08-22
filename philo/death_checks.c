/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:00:56 by mleibeng          #+#    #+#             */
/*   Updated: 2024/01/22 20:47:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death_flag(t_philo *philo)
{
	if (!(*philo->confirmed_death))
		return (0);
	return (1);
}

int	check_starvation(t_philo *watchguard)
{
	t_philo	*individual;
	int		i;

	i = -1;
	while (++i < watchguard->databank->num_of_phils)
	{
		individual = &watchguard[i];
		pthread_mutex_lock(individual->lock_eating);
		if (timer_start()
			- individual->timestamp_last_meal
			>= watchguard->databank->deathdelay)
		{
			print_function(individual, "has died\n",
				individual->timestamp_last_meal);
			*(watchguard->confirmed_death) = 1;
			return (pthread_mutex_unlock(individual->lock_eating), 1);
		}
		pthread_mutex_unlock(individual->lock_eating);
	}
	return (0);
}
