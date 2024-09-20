/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/20 15:16:35 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (res < LONG_MIN || res > LONG_MAX)
			exit(OUT_OF_RANGE);
		i++;
	}
	return ((res * sign) % 256);
}

static int	__set_exit_status(t_data *d, char **args)
{
	long long	exit_status;

	exit_status = 0;
	if (args == NULL || args[1] == NULL)
		exit_status = d->last_exit_status;
	else if (args[1] != NULL)
	{
		if (ft_strisnumeric(args[1]) == 0 && args[2] != NULL)
			return (err_msg_cmd("exit", NULL, "too many arguments", FAILURE));
		else
			exit_status = __ft_atol(args[1]);
	}
	else
		return (err_msg_cmd("exit", args[1], "numeric argument required", 2));
	return (exit_status);
}

void	my_exit(t_data *d, char **args)
{
	int	exit_status;
	
	exit_status = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_status = __set_exit_status(d, args);
	if (exit_status != 1)
		clean_exit_shell(exit_status);
}
