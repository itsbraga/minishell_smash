/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/04 19:21:45 by annabrag         ###   ########.fr       */
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
	while (arg[i] != '\0' && ft_isspace(arg[i]) == 1)
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
		i++;
	}
	return ((res * sign) % 256);
}

static bool	__is_overflow(char *arg)
{
	int		i;
	size_t	len;

	i = 0;
	while (arg[i] != '\0' && ft_isspace(arg[i]) == 1)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	len = ft_strlen(&arg[i]);
	if (len > 19)
		return (true);
	if (len == 19)
	{
		if (arg[0] == '-' && ft_strcmp(&arg[i], "9223372036854775808") > 0)
			return (true);
		if (arg[0] != '-' && ft_strcmp(&arg[i], "9223372036854775807") > 0)
			return (true);
	}
	return (false);
}

static int	__get_exit_status(char **args)
{
	long long	code;

	code = 0;
	if (args[1] == NULL)
		code = ft_exit_status(0, GET);
	else
	{
		if (ft_strisnumeric(args[1]) == 1 && args[2] != NULL)
			code = err_msg_cmd("exit", NULL, ERR_ARG, FAILURE);
		else if (ft_strisnumeric(args[1]) == 0)
			code = err_msg_cmd("exit", args[1], ERR_ARG_TYPE, BAD_USAGE);
		else if (__is_overflow(args[1]) == true)
			code = err_msg_cmd("exit", args[1], ERR_ARG_TYPE, BAD_USAGE);
		else
			code = __ft_atol(args[1]);
	}
	return (ft_exit_status(code, ADD));
}

int	ft_exit(char **args)
{
	int	code;

	code = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	code = __get_exit_status(args);
	if (code != FAILURE)
		clean_exit(code);
	return (ft_exit_status(FAILURE, ADD));
}
