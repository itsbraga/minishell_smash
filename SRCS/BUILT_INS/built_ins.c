/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/22 20:47:33 by art3mis          ###   ########.fr       */
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
		ft_echo(d, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(d);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(d->exp_env, d->env, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(d, cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1] != NULL)
		{
			err_msg(cmd[1], ERR_BAD_FILE, 1);
			return (d->last_exit_status = 127);
		}
		ft_env(d->env);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(d, cmd);
	else if (ft_strcmp(cmd[0], "clear") == 0)
		printf("\033[H\033[J");
	return (d->last_exit_status = SUCCESS);
}
