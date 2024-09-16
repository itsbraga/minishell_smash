/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:38:47 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 13:03:38 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_exec.h"

void    init_and_fill_e_info(t_exec_info *e_info, int cmd_nb)
{
    e_info->cmd_count = cmd_nb;
	e_info->executed_cmd = 0;
	e_info->pipe_count = e_info->cmd_count - 1;
	e_info->fd[0] = 0;
	e_info->fd[1] = 0;
	e_info->old_read_fd = 0;
	e_info->child_pid = 0;
}