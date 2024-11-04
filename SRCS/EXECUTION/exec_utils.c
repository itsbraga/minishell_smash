/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:24:08 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/03 23:23:35 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*build_path_to_try(char *cmd, char *tab_path_to_join)
{
	char	*path_to_try;
	char	*tmp;

	tmp = ft_strjoin(tab_path_to_join, "/");
	secure_malloc(tmp, true);
	path_to_try = ft_strjoin(tmp, cmd);
	secure_malloc(path_to_try, true);
	yama(ADD, path_to_try, 0);
	free_and_set_null((void **)&tmp);
	return (path_to_try);
}

char	*search_bin(char *cmd, char **tab_path)
{
	char	*path_to_try;
	int		i;

	i = 0;
	while (tab_path[i] != NULL)
	{
		path_to_try = build_path_to_try(cmd, tab_path[i]);
		if (access(path_to_try, F_OK) == -1)
		{
			yama(REMOVE, path_to_try, 0);
			i++;
		}
		else
		{
			if (check_if_is_dir(path_to_try) == false)
				return ((void)yama(REMOVE, tab_path, 0), path_to_try);
			else
				return ((void)yama(REMOVE, tab_path, 0), NULL);
		}
	}
	return ((void)yama(REMOVE, tab_path, 0), NULL);
}

int	check_given_path(t_exec_lst *node)
{
	if (check_if_is_dir(node->bin_path) == true)
	{
		err_msg(node->bin_path, ERR_IS_DIR, 0);
		clean_exit(CMD_CANNOT_EXEC);
	}
	if (access(node->bin_path, F_OK) == -1)
	{
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_FILE, CMD_NOT_FOUND);
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_built_path(t_exec_lst *node)
{
	if (node->bin_path == NULL)
	{
		err_msg_cmd(node->cmd[0], NULL, ERR_CMD, CMD_NOT_FOUND);
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		return (FAILURE);
	}
	return (SUCCESS);
}
