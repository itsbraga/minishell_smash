/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/03 23:23:35 by art3mis          ###   ########.fr       */
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
		if (waitpid(-1, &status, 0) == -1)
		{
			err_msg("waitpid", strerror(errno), 0);
			clean_exit(FAILURE);
		}
		if (WIFEXITED(status))
			ft_exit_status(WEXITSTATUS(status), ADD);
		child_count--;
	}
}

static void	__parent(t_exec_info *info, t_exec_lst *curr)
{
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
			clean_exit(FAILURE);
	}
	d->info->child_pid = fork();
	if (d->info->child_pid == -1)
		clean_exit(FAILURE);
	if (d->info->child_pid == 0)
		pathfinder(d, curr);
	else
		__parent(d->info, curr);
}

static int	__before_while_cmd(t_data *d, t_exec_lst **e_lst)
{
	int	check_behaviour;

	check_behaviour = 0;
	if (d->info->all_cmd_heredoc_nb > 16)
	{
		err_msg(NULL, ERR_MAX_HD, 0);
		clean_exit(BAD_USAGE);
	}
	if (handle_heredoc(d, e_lst) == STOP_EXEC)
		return (STOP_EXEC);
	if ((*e_lst)->cmd != NULL && d->info->cmd_count == 1)
	{
		check_behaviour = execute_parent_built_in(d, (*e_lst)->cmd);
		if (check_behaviour == NOT_A_BUILTIN || check_behaviour == CD_CASE)
			return (SUCCESS);
		else
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
		set_signals_in_exec();
		while (curr != NULL && (d->info->executed_cmd != d->info->cmd_count))
		{
			__handle_exec_node(d, curr);
			curr = curr->next;
		}
		__wait_child(d->info);
	}
}
