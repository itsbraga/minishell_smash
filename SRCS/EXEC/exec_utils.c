/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:24:08 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/07 18:44:17 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bin_path(t_exec_lst *node, bool absolute_path)
{
	if (access(node->bin_path, F_OK) == -1)
	{
		if (absolute_path == true)
			err_msg_cmd(node->bin_path, NULL, ERR_BAD_FILE, 127);
		else
			err_msg_cmd(node->cmd[0], NULL, ERR_CMD, 127);
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

char	**search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	all_path = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
		{
			all_path = env[i];
			break;
		}
	}
	if (all_path != NULL)
	{
		tab_path = yama(ADD_TAB, ft_split(all_path, ':'), 0);
		if (tab_path == NULL)
		{
			perror("malloc");
			clean_exit_shell(FAILURE);
		}
	}
	return (tab_path);
}

char	*search_bin(char *cmd, char **tab_path)
{
	char	*path_to_try;
	char	*tmp;
	int		i;

	i = 0;
	while (tab_path[i] != NULL)
	{
		tmp = ft_strjoin(tab_path[i], "/");
		secure_malloc(tmp);
		(void)yama(ADD, tmp, 0);
		path_to_try = ft_strjoin(tmp, cmd);
		secure_malloc(path_to_try);
		(void)yama(ADD, path_to_try, 0);
		(void)yama(REMOVE, tmp, 0);
		if (access(path_to_try, F_OK) == -1)
		{
			(void)yama(REMOVE, path_to_try, 0);
			i++;
		}
		else
			return(yama(REMOVE, tab_path, 0), path_to_try);
	}
	return(yama(REMOVE, tab_path, 0), NULL);
}
