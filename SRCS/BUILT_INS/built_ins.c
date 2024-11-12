/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/04 19:13:51 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_child_built_in(t_data *d, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(cmd));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(&(d->env), cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_exit_status(SUCCESS, ADD));
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (d->info->cmd_count == 1)
			return (ft_exit_status(0, GET));
		else
			return (ft_exit_status(SUCCESS, ADD));
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_exit_status(SUCCESS, ADD));
	return (NOT_A_BUILTIN);
}

int	execute_parent_built_in(t_data *d, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(&(d->exp_env), &(d->env), cmd));
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(d, cmd);
		return (CD_CASE);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(d, cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd));
	return (NOT_A_BUILTIN);
}
