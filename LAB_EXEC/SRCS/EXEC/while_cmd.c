/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 18:48:42 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/mini_exec.h"

void	go_exec(t_exec_lst *node, t_env_lst **env)
{
	char *all_path;
	
	all_path = NULL;
	if (node->is_absolute_path == true)
		check_bin_path(node);
	else
	{
		all_path = search_path();
		if (all_path == NULL)
		{
			printf("%s: command not found\n", node->cmd[0]);
			return;
		}
		else
			node->path_bin = search_path_bin();
	}
	exec(node);
}

void	pathfinder(t_exec_lst *node, t_exec_info *e_info, t_env_lst **env)
{
	if (node->red_in != NULL)
		redirection_in();
	else if (e_info->executed_cmd != 0)
	{
		dup2(e_info->old_read_fd, STDIN_FILENO);
		close(e_info->old_read_fd);
	}
	if (node->red_out != NULL)
		redirection_out();
	else if (e_info->executed_cmd != (e_info->cmd_count) - 1)
		dup2(e_info->fd[1], STDOUT_FILENO);
	close(e_info->fd[0]);
	close(e_info->fd[1]);
	go_exec(node, env);
}

void	while_cmd(t_exec_lst **e_lst, t_exec_info *e_info, t_env_lst **env)
{
	t_exec_lst *node;

	while (e_info->executed_cmd != e_info->cmd_count && node != NULL)
	{
		node = *e_lst;
		if (e_info->pipe_count)
			if (pipe(e_info->fd) == -1)
				clean_exit();
		e_info->child_pid = fork();
		if (e_info->child_pid == -1)
			clean_exit();
		if (!e_info->child_pid)
			pathfinder(node, e_info, env);
		else
			parent();
		node = node->next;
		e_info->cmd_count--;
	}	
}

//NOTES :
// - Je dois reperer la presence de pipe, et ne surtout pas en ouvrir si il n'y
//		en a pas.
// - cas d'erreur lorsque chemin relatif et que $PATH n'existe pas