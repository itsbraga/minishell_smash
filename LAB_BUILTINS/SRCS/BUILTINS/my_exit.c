/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:27:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/27 02:26:59 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static long	__ft_atol(char *arg)
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
			exit(OUT_OF_RANGE);
	}
	return (res * sign);
}

static void	__set_exit_status(t_global *g, char **args)
{
	int		exit_status; // ou caster quand on appelle exit

	exit_status = 0;
	if (args == NULL || args[1] == NULL)
		exit_status = 0; // g_last_exit_status
	else if (args[2] != NULL)
		errmsg_status("exit", args[2], FAILURE);
	else if (ft_isdigit(args[1]) == 1)
		exit_status = __ft_atol(args[1]);
	else
		errmsg_status("exit", args[1], MISUSE_BUILTIN);
	exit(exit_status % 256);	
}

// void	exit_minishell(t_global *g, int err_status)
// {
// 	if (g != NULL)
// 		// free_global(g);
// 	exit(err_status);
// }

int	my_exit(t_global *g)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	// __set_exit_status(g, ?);
	return (SUCCESS);
}
