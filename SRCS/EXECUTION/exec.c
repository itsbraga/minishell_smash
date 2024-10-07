/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/07 22:32:13 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free(path_bin);
		path_bin = NULL;
		return ; // à changer
	}
}

static int	__check_bin_path(t_exec_lst *node, bool absolute_path)
{
	if (access(node->bin_path, F_OK) == -1)
	{
		if (absolute_path == true)
			err_msg_cmd(node->bin_path, NULL, ERR_BAD_FILE, CMD_NOT_FOUND);
		else
			err_msg_cmd(node->cmd[0], NULL, ERR_CMD, CMD_NOT_FOUND);
		free(node->bin_path);
		node->bin_path = NULL;
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		free(node->bin_path);
		node->bin_path = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	handle_bin_path(t_exec_lst *node, char **env)
{
	int	error;
	char **tab_path;
	
	error = 0;
	tab_path = NULL;
	if (node->absolute_path == true)
		error = __check_bin_path(node, node->absolute_path);
	else
	{
		tab_path = search_path(tab_path, env);
		if (tab_path == NULL)
		{
			err_msg(NULL, ERR_NO_ENV, 0);
			error = 1;
		}
		else
			node->bin_path = search_bin(node->cmd[0], tab_path);
		if (node->bin_path != NULL)
			error = __check_bin_path(node, node->absolute_path);
	}
	return (error);
}

void	go_exec(t_exec_lst *node, char **env)
{
	if (handle_bin_path(node, env) == 0)
		exec(node->bin_path, node->cmd, env);
	else
		return ;
}
// gerer le cas des redirections seules (aucune commande)