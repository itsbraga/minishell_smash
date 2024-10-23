/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/23 19:33:37 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_built_in(char *cmd)
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
		if (ft_strcmp(built_in[i++], cmd) == 0)
			return (true);
	}
	return (false);
}

int	execute_built_in(t_data *d, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(d, cmd));
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
		ft_exit(d, cmd);
	else
		return
	d->last_exit_status = SUCCESS;
	return (d->last_exit_status);
}
