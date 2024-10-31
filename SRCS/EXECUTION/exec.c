/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/31 08:30:16 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute(char *bin_path, char **cmd_and_args, char **env)
{
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	close(data_struct()->fd_stdin_backup); 
	if (execve(bin_path, cmd_and_args, env) == -1)
	{
		if (errno == EACCES)
		{
			err_msg_cmd(bin_path, NULL, strerror(errno), 0);
			clean_exit_shell(ft_exit_status(CMD_CANNOT_EXEC, ADD));
		}
		else
		{
			err_msg_cmd(bin_path, NULL, strerror(errno), 0);
			clean_exit_shell(ft_exit_status(FAILURE, ADD));
		}
	}
}

int	handle_bin_path(t_exec_lst *node, char **env)
{
	int		error;
	char	**tab_path;

	error = 0;
	tab_path = NULL;
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	if (node->absolute_path == true)
		error = check_given_path(node);
	else if (node->absolute_path == false)
	{
		tab_path = search_path(tab_path, env);
		if (tab_path == NULL)
		{
			err_msg(NULL, ERR_NO_ENV, 0);
			error = 1;
		}
		else
		{
			node->bin_path = search_bin(node->cmd[0], tab_path);
			// dprintf(2, "bin path = %s\n", node->bin_path);
			error = check_built_path(node);
		}
	}
	return (error);
}

void	go_exec(t_exec_lst *node)
{
	t_data	*d;
	int 	ret;
	char	**env_tab;

	// dprintf(2, "PID[%d] | go_exec\n", getpid());
	d = data_struct();
	ret = 0;
	env_tab = NULL;
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	ret = execute_child_built_in(d, node->cmd);
	if (ret != NOT_A_BUILTIN)
		clean_exit_shell(ft_exit_status(0, GET));
	else if (ret == NOT_A_BUILTIN)
	{
		// if (d->info->executed_cmd == 1)
		// 	usleep(500);
		env_tab = recreate_env_tab(&(d->env));
		if (handle_bin_path(node, env_tab) == SUCCESS)
			execute(node->bin_path, node->cmd, env_tab);
		else
		{
			dprintf(2, "PID[%d] | handle bin path failure\n", getpid());
			yama(REMOVE, env_tab, 0);
			clean_exit_shell(ft_exit_status(0, GET));
		}
	}
}
