/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:46:34 by marvin            #+#    #+#             */
/*   Updated: 2024/01/27 04:19:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	false_value_parse(char *arg)
{
	int	i;

	i = 0;
	if (ft_issign(arg[i]) && arg[i + 1])
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] && !ft_isdigit(arg[i]))
		return (1);
	return (0);
}

int	false_value_check(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (false_value_parse(args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	if (false_value_check(argv))
		return (1);
	if (ft_atoi(argv[1]) > MAX_PHILO || ft_atoi(argv[1]) < 0 || (argc == 6
			&& ft_atoi(argv[5]) < 0))
		return (1);
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}
