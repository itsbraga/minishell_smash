/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 19:14:55 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/mini_exec.h"

void	pathfinder(t_exec_lst *node, t_exec_info *e_info, char **env)
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