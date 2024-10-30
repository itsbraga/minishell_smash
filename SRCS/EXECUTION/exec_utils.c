/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:24:08 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/30 04:24:37 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	all_path = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
		{
			all_path = env[i];
			break ;
		}
	}
	if (all_path != NULL)
	{
		tab_path = yama(ADD_TAB, ft_split(all_path, ':'), 0);
		secure_malloc(tab_path, true);
	}
	return (tab_path);
}

char	*search_bin(char *cmd, char **tab_path)
{
	char	*path_to_try;
	char	*tmp;
	int		i;

	i = 0;
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	while (tab_path[i] != NULL)
	{
		tmp = ft_strjoin(tab_path[i], "/");
		secure_malloc(tmp, true);
		(void)yama(ADD, tmp, 0);
		path_to_try = ft_strjoin(tmp, cmd);
		secure_malloc(path_to_try, true);
		(void)yama(ADD, path_to_try, 0);
		(void)yama(REMOVE, tmp, 0);
		if (access(path_to_try, F_OK) == -1)
		{
			(void)yama(REMOVE, path_to_try, 0);
			i++;
		}
		else
			return ((void)yama(REMOVE, tab_path, 0), path_to_try);
	}
	return ((void)yama(REMOVE, tab_path, 0), NULL);
}

static bool	__check_if_is_dir(char *bin_path)
{
	struct stat	s_bin_path;

	if (stat(bin_path, &s_bin_path) == 0)
	{
		if (S_ISDIR(s_bin_path.st_mode) != 0)
		{
			err_msg(bin_path, ERR_IS_DIR, 0);
			return (true);
		}
	}
	return (false);
}

int	check_given_path(t_exec_lst *node)
{
	if (__check_if_is_dir(node->bin_path) == true)
		clean_exit_shell(ft_exit_status(CMD_CANNOT_EXEC, ADD));
	if (access(node->bin_path, F_OK) == -1)
	{
		ft_exit_status(CMD_NOT_FOUND, ADD);
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_FILE, CMD_NOT_FOUND);
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		ft_exit_status(CMD_CANNOT_EXEC, ADD);
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_built_path(t_exec_lst *node)
{
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	if (node->bin_path == NULL)
	{
		ft_exit_status(CMD_NOT_FOUND, ADD);
		err_msg_cmd(node->cmd[0], NULL, ERR_CMD, CMD_NOT_FOUND);
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		ft_exit_status(CMD_CANNOT_EXEC, ADD);
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		return (FAILURE);
	}
	return (SUCCESS);
}
