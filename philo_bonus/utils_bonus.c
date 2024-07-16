/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 04:03:19 by mleibeng          #+#    #+#             */
/*   Updated: 2024/01/28 16:51:14 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_function(t_philo *philo, char *string)
{
	sem_wait(philo->databank->lock_messaging);
	printf("%zu %d %s", timer_start() - philo->databank->init_time,
		philo->ident, string);
	sem_post(philo->databank->lock_messaging);
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
