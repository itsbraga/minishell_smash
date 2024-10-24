/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/24 21:18:20 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_built_in(char **cmd)
{
	int			i;
	const char	*built_in[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	i = 0;
	while (built_in[i] != NULL)
	{
		if (ft_strcmp(built_in[i], *cmd) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	execute_built_in(t_data *d, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(d));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(d->exp_env, d->env, cmd));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(d, cmd));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(d->env, cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	return (NOT_A_BUILTIN);
}
