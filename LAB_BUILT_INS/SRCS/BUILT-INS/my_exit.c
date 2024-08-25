/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/25 21:52:39 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	__has_only_one_arg(char **args)
{
	if (args[2] != NULL)
		return (false);
	return (true);
}

static long	__ft_atol(char *arg, bool *error)
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
			*error = true;
			// exit (255);
		i++;
	}
	return (res * sign);
}

static int	__get_exit_status(t_global *g, char *arg, bool *error)
{
	long long	status;
	int			i;

	status = 0;
	i = 0;
	if (arg == NULL)
		return (g->last_exit_status);
	while (ft_isspace(arg[i]) == 1)
		i++;
	if (arg[i] == '\0')
		*error = true;
		// exit (EXIT_FAILURE); || return (g->last_exit_status);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && ft_isspace(arg[i]) == 0)
			*error = true;
			// exit (128); || break ;
		i++;
	}
	status = __ft_atol(arg, error);
	return (status % 256);	
}

void	my_exit(t_global *g, char **args)
{
	int		status;
	bool	error;
	bool	correct_input;

	status = 0;
	error = false;
	if (args == NULL || args[1] == NULL)
		status = g->last_exit_status;
	correct_input = __has_only_one_arg(args);
	if (correct_input == false)
	{
		error = true;
		errmsg("exit", NULL);
	}
	else
	{
		status = __get_exit_status(g, *args, &error);
		if (error == true)
			errmsg_status("exit", NULL, errno);
			// verifier sur arg == NULL
	}
}
