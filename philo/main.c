/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:38:17 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 21:47:07 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7
//	- No Philosopher should die and the simulation
// should stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.

void	cleanup_func(t_discussion *program, t_databank *data,
		pthread_t *watchguard, int creation_result)
{
	int	i;

	i = -1;
	if (creation_result >= 1)
		pthread_join(*watchguard, NULL);
	if (creation_result >= 2)
	{
		while (++i < data->num_of_phils)
			pthread_join(program->philos[i].thread, NULL);
	}
	pthread_mutex_destroy(&program->lock_eating);
	pthread_mutex_destroy(&program->lock_messaging);
	i = -1;
	while (++i < data->num_of_phils)
		pthread_mutex_destroy(program->philos[i].left_f);
}

int	main(int argc, char **argv)
{
	t_discussion	program;
	t_databank		databank;

	if (check_args(argc, argv))
		return (1);
	init_databank(&databank, argv, argc);
	if (init_program(&program, &databank))
		return (1);
	return (0);
}
