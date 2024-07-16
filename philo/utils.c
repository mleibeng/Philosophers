/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 04:03:19 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/29 14:57:34 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_function(t_philo *philo, char *string)
{
	pthread_mutex_lock(philo->lock_messaging);
	printf("%zu %d %s", timer_start() - philo->databank->init_time,
		philo->tid, string);
	pthread_mutex_unlock(philo->lock_messaging);
}

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t			i;
	unsigned char	*scmp1;
	unsigned char	*scmp2;

	i = 0;
	scmp1 = (unsigned char *)s1;
	scmp2 = (unsigned char *)s2;
	if (size == 0)
		return (0);
	while (i < size - 1 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (scmp1[i] - scmp2[i]);
		i++;
	}
	return (scmp1[i] - scmp2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
