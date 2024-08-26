/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:08:53 by mleibeng          #+#    #+#             */
/*   Updated: 2024/08/26 11:51:45 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		return (printf("getttimeofday error", NULL));
	return (ms_timer(measure_timer.timer));
}

// int	check_timer(t_timer *measured)
// {
// 	struct timeval	current_time;
// 	long int		time_diff_ms;

// 	if (gettimeofday(&current_time, NULL))
// 	{
// 		printf("error in checktimer");
// 		return (-1);
// 	}
// 	time_diff_ms = ms_timer(current_time) - ms_timer(measured->start_time);
// 	return (time_diff_ms >= measured->ms_duration);
// }

// int	timeval_cmp(const struct timeval *a, const struct timeval *b)
// {
// 	if (a->tv_sec < b->tv_sec)
// 		return (1);
// 	else if (a->tv_sec > b->tv_sec)
// 		return (-1);
// 	else
// 	{
// 		if (a->tv_usec < b->tv_usec)
// 			return (1);
// 		else if (a->tv_usec > b->tv_usec)
// 			return (-1);
// 		else
// 			return (0);
// 	}
// }

// void timeval_sub(const struct timeval *a, const struct timeval *b,
// struct timeval *res) {
// 	res->tv_sec = a->tv_sec - b->tv_sec;
// 	res->tv_usec = a->tv_usec - b->tv_usec;

// 	if (res->tv_usec < 0) {
// 		res->tv_sec--;
// 		res->tv_usec += 1000000;
// 	}
// }

void	improved_sleep(size_t time_delay, t_philo *philo)
{
	t_timer	current_time;

	current_time.start_time = timer_start();
	while (timer_start() - current_time.start_time < time_delay)
	{
		usleep(100);
		if (*(philo->confirmed_death))
			return ;
	}
}
