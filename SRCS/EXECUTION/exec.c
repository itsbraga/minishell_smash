/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/24 21:51:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	dprintf(2, "PID : %d | before execve (exec)\n", getpid());
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		dprintf(2, "PID : %d | execve failed /!\\(exec)\n", getpid());
		free_and_set_null(path_bin);
		exit(ft_exit_status(FAILURE, ADD)); // à changer ---> clean_exit_shell(errno) ?
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	if (is_built_in(node->cmd) == false)
	{
		if (handle_bin_path(node, env) == 0)
			exec(node->bin_path, node->cmd, env);
		else
		{
			yama(REMOVE, env, 0);
			exit(ft_exit_status(FAILURE, ADD));
		}
	}
	else
	{
		if (execute_built_in(d, node->cmd) == FAILURE)
		{
			err_msg(node->cmd[0], strerror(errno), 0);
			yama(REMOVE, env, 0);
			exit(ft_exit_status(FAILURE, ADD));
		}
	}
}
