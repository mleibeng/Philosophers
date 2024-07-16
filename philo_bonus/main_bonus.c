/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:38:17 by marvin            #+#    #+#             */
/*   Updated: 2024/01/28 18:11:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7
//	- No Philosopher should die and the simulation
// should stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.

void	cleanup_func(t_philo *philos, sem_t *forks)
{
	int	i;

	i = -1;
	while (++i < philos->databank->num_of_phils)
		kill(philos[i].pid, SIGKILL);
	sem_close(philos->databank->lock_counter);
	sem_close(philos->databank->exit_process);
	sem_close(philos->databank->lock_eating);
	sem_close(philos->databank->lock_messaging);
	sem_close(forks);
}

int	main(int argc, char **argv)
{
	t_philo		philos[MAX_PHILO];
	t_databank	databank;

	if (check_args(argc, argv))
		return (1);
	if (init_databank(&databank, argv, argc))
		return (1);
	if (init_program(philos, &databank))
		return (1);
	return (0);
}
