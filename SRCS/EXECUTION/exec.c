/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 19:14:40 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute(char *bin_path, char **cmd_and_args, char **env)
{
	close(data_struct()->fd_stdin_backup);
	if (execve(bin_path, cmd_and_args, env) == -1)
	{
		if (errno == EACCES)
		{
			err_msg_cmd(bin_path, NULL, strerror(errno), 0);
			clean_exit(CMD_CANNOT_EXEC);
		}
		else
		{
			err_msg_cmd(bin_path, NULL, strerror(errno), 0);
			clean_exit(FAILURE);
		}
	}
}

int	handle_bin_path(t_exec_lst *node, char **env)
{
	int		error;
	char	**tab_path;

	error = 0;
	tab_path = NULL;
	if (node->is_given_path == true)
		error = check_given_path(node);
	else if (node->is_given_path == false)
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
			error = check_built_path(node);
		}
	}
	return (error);
}

void	go_exec(t_exec_lst *node)
{
	int		ret;
	char	**env_tab;

	ret = 0;
	env_tab = NULL;
	ret = execute_child_built_in(data_struct(), node->cmd);
	if (ret != NOT_A_BUILTIN)
		clean_exit(ft_exit_status(0, GET));
	else if (ret == NOT_A_BUILTIN)
	{
		env_tab = recreate_env_tab(&(data_struct()->env));
		if (handle_bin_path(node, env_tab) == SUCCESS)
			execute(node->bin_path, node->cmd, env_tab);
		else
		{
			yama(REMOVE, env_tab, 0);
			clean_exit(ft_exit_status(0, GET));
		}
	}
}
