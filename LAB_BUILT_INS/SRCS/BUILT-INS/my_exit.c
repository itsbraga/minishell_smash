/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/25 16:30:54 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	__isnumeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static bool	__has_only_one_arg(char **cmd)
{
	if (cmd[2] != NULL)
		return (false);
	return (true);
}

static long	__ft_atol(const char *arg)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (arg[i] != '\0' && (ft_isspace(arg[i]) == 1))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign *= -1;
		i++;
	}
	while (arg[i] != '\0' && (ft_isdigit(arg[i]) == 0))
	{
		res = res * 10 + (arg[i] - 48);
		if (res < LONG_MIN || res > LONG_MAX)
			exit (255);
		i++;
	}
	return (res * sign);
}

static long	__get_exit_code(char *arg)
{
	
};

void	my_exit();