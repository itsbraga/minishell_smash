/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/14 19:39:46 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/mini_exec.h"

void	while_cmd(t_exec_lst **e_lst, t_exec_info *e_info, t_env_lst **env)
{
	while (e_info->cmd_count)
	{
		if (e_info->pipe_count)
			if (pipe(e_info->fd) == -1)
				clean_exit();
		e_info->child_pid = fork();
		if (e_info->child_pid == -1)
			clean_exit();
		if (!e_info->child_pid)
			pathfinder();
		else
			parent();
	}	
}

//NOTES :
// - Je dois reperer la presence de pipe, et ne surtout pas en ouvrir si il n'y
//		en a pas.
// - 