/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:08:53 by mleibeng          #+#    #+#             */
/*   Updated: 2024/08/15 20:05:42 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdint.h>

size_t	ms_timer(struct timeval time)
{
	size_t	result;
	size_t	usec_ms;

	result = time.tv_sec * 1000;
	if (time.tv_usec > 0)
	{
		usec_ms = time.tv_usec / 1000;
		if (SIZE_MAX - result < usec_ms)
		{
			printf("error in ms_timer");
			return (SIZE_MAX);
		}
		result += usec_ms;
	}
	return (result);
}

size_t	timer_start(void)
{
	t_timer	measure_timer;

	if (gettimeofday(&(measure_timer.timer), NULL) == -1)
		return (printf("getttimeofday error"));
	return (ms_timer(measure_timer.timer));
}

void	improved_sleep(size_t time_delay)
{
	t_timer	current_time;

	current_time.start_time = timer_start();
	while (timer_start() - current_time.start_time < time_delay)
		usleep(100);
}
