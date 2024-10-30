/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/30 04:11:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	__wait_child(t_exec_info *info)
{
	int	status;
	int	child_count;

	child_count = info->cmd_count;
	while (child_count != 0)
	{
		// printf("PID : %d | waiting for child... (wait_child)\n", getpid());
		if (waitpid(-1, &status, 0) == -1)
			(err_msg("waitpid", strerror(errno), 0), clean_exit_shell(FAILURE));
		if (WIFEXITED(status))
			ft_exit_status(WEXITSTATUS(status), ADD);
		child_count--;
		// printf("PID : %d | a child is done ! (wait_child)\n", getpid());
	}
	// printf("PID : %d | no more child to wait (wait_child)\n", getpid());
}

static void	__parent(t_exec_info *info, t_exec_lst *curr)
{
	// printf("PID : %d | parent\n", getpid());
	if (info->pipe_count != 0)
	{
		close(info->fd[1]);
		if (info->executed_cmd != 0)
			close(info->old_read_fd);
		info->old_read_fd = info->fd[0];
		if (info->executed_cmd == info->cmd_count - 1)
			close(info->fd[0]);
	}
	if (curr->latest_hd != 0)
		close(curr->latest_hd);
	info->executed_cmd++;
}

static void	__handle_exec_node(t_data *d, t_exec_lst *curr)
{
	if (d->info->pipe_count != 0
			&& (d->info->executed_cmd != d->info->cmd_count - 1))
		{
			if (pipe(d->info->fd) == -1)
				clean_exit_shell(FAILURE);
		}
		d->info->child_pid = fork();
	if (d->info->child_pid == -1)
		clean_exit_shell(FAILURE);
	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	if (d->info->child_pid == 0)
		pathfinder(d, curr);
	else
		__parent(d->info, curr);
}

static int	__before_while_cmd(t_data *d, t_exec_lst **e_lst)
{
	if (d->info->all_cmd_heredoc_nb > 16)
	{
		err_msg(NULL, ERR_MAX_HD, 0);
		clean_exit_shell(BAD_USAGE);
	}
	if (handle_heredoc(d, e_lst) == STOP_EXEC)
		return (STOP_EXEC);
	if ((*e_lst)->cmd != NULL && d->info->cmd_count == 1)
	{
		if (execute_parent_built_in(d, (*e_lst)->cmd) != NOT_A_BUILTIN)
			return (STOP_EXEC);
	}
	return (SUCCESS);
}

void	while_cmd(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*curr;
	int			check_behaviour;

	curr = *e_lst;
	check_behaviour = __before_while_cmd(d, e_lst);
	if (check_behaviour != STOP_EXEC)
	{
		while (curr != NULL && (d->info->executed_cmd != d->info->cmd_count))
		{
			dprintf(2, "in while_cmd | pipecount = %d\n", d->info->pipe_count);
			__handle_exec_node(d, curr);
			curr = curr->next;
		}
		__wait_child(d->info);
	}
	dprintf(2, "out while_cmd\n");
}
