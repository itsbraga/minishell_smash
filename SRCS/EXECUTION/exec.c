/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/24 22:59:24 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free_and_set_null(path_bin);
		exit(ft_exit_status(FAILURE, ADD));
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	int ret;

	ret = 0;
	ret = execute_built_in(d, node->cmd)
	if (ret == FAILURE || ret == BAD_USAGE)
	{
		yama(REMOVE, env, 0);
		exit(ft_exit_status(0, GET));
	}
	else if (ret == NOT_A_BUILTIN)
	{
		if (handle_bin_path(node, env) == 0)
			exec(node->bin_path, node->cmd, env);
		else
		{
			yama(REMOVE, env, 0);
			exit(ft_exit_status(0, GET));
		}
	}
}
