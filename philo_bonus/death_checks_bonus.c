/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:00:56 by mleibeng          #+#    #+#             */
/*   Updated: 2024/01/28 16:39:21 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	check_starvation(t_philo *watchguard)
{
	if (timer_start() - watchguard->timestamp_last_meal
		>= watchguard->databank->deathdelay
		&& !watchguard->confirmed_death)
	{
		print_function(watchguard, "has died\n");
		watchguard->confirmed_death = 1;
		sem_post(watchguard->databank->exit_process);
		while (1)
			sem_post(watchguard->databank->lock_counter);
	}
}

void	*check_death_flag(void *phil)
{
	t_philo	*philos;

	philos = (t_philo *)phil;
	while (1)
	{
		if (philos->sated)
			sem_post(philos->databank->exit_process);
		sem_wait(philos->databank->lock_eating);
		check_starvation(philos);
		sem_post(philos->databank->lock_eating);
	}
	return (NULL);
}
