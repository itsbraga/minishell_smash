/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/26 16:37:38 by annabrag         ###   ########.fr       */
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
		res = res * 10 + (arg[i++] - 48);
		if (res < LONG_MIN || res > LONG_MAX)
		{
			*error = true;
			break ;
		}
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
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && ft_isspace(arg[i]) == 0)
			*error = true;
		i++;
	}
	status = __ft_atol(arg, error);
	return (status % 256);	
}

void	exit_minishell(t_global *g, int err_status)
{
	if (g != NULL)
		// free_global(g);
		lstclear_tokens(&g->token);
	exit(err_status);
}

// gerer le cas ou exit est appele seul
int	my_exit(t_global *g, char **args)
{
	int		exit_status;
	bool	error;
	bool	correct_input;
 
	exit_status = 0;
	error = false;
	if (args == NULL || args[1] == NULL)
		exit_status = g->last_exit_status;
	correct_input = __has_only_one_arg(args);
	if (correct_input == false)
		errmsg("exit", NULL);
	else
	{
		exit_status = __get_exit_status(g, args[1], &error);
		if (error == true)
			errmsg_status("exit", args[1], MISUSE_BUILTIN);
		else if (args[2] != NULL)
			errmsg_status("exit", NULL, MISUSE_BUILTIN);
	}
	exit_minishell(g, exit_status);
	return (MISUSE_BUILTIN);
}
