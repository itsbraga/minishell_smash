/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 19:15:16 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free(path_bin);
		//free_child_tab ?
		return;//à changer
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	char *all_path;
	
	all_path = NULL;
	if (node->is_absolute_path == true)
		check_bin_path(node);
	else
	{
		all_path = search_path(env);
		if (all_path == NULL)
		{
			printf("\033[1;5;31m - Environment variable doesn't exist, ");
			printf("please specify absolute path. - \n\033[0m");
			return; // à changer
		}
		else
			node->path_bin = search_path_bin();
	}
	if (node->path_bin != NULL)
		exec(node->path_bin, node->cmd, env);
	else
	{
		printf("minishell: command not found\n");
		return;//à changer
	}
}