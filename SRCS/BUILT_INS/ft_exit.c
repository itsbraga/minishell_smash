/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/25 19:09:09 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static long long	__ft_atol(char *arg)
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
	while (arg[i] != '\0' && ft_isdigit(arg[i]) == 1)
	{
		res = res * 10 + (arg[i] - 48);
		if (res < LONG_MIN || res > LONG_MAX)
			exit(OUT_OF_RANGE);
		i++;
	}
	return ((res * sign) % 256);
}

static int	__get_exit_status(char **args)
{
	long long	exit_status;

	exit_status = 0;
	if (args == NULL || args[1] == NULL)
		exit_status = ft_exit_status(0, GET);
	else if (args[1] != NULL)
	{
		if ((ft_strisnumeric(args[1]) == 0) && args[2] != NULL)
		{
			ft_exit_status(FAILURE, ADD);
			return (err_msg_cmd("exit", NULL, ERR_ARG, FAILURE));
		}
		else if ((ft_strisnumeric(args[1]) != 0) && args[2] != NULL)
		{
			ft_exit_status(BAD_USAGE, ADD);
			return (err_msg_cmd("exit", args[1], ERR_ARG_TYPE, BAD_USAGE));
		}
		else
			exit_status = __ft_atol(args[1]);
	}
	return (ft_exit_status(exit_status, ADD));
}

int	ft_exit(char **args)
{
	int	exit_status;

	exit_status = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_status = __get_exit_status(args);
	if (exit_status >= 2)
	{
		clean_exit_shell(exit_status);
		return (ft_exit_status(exit_status, ADD));
	}
	else
		return (ft_exit_status(0, GET));
}
