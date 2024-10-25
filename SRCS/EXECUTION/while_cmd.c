/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/25 21:05:53 by pmateo           ###   ########.fr       */
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
		printf("PID : %d | waiting for child... (wait_child)\n", getpid());
		if (waitpid(-1, &status, 0) == -1)
			(err_msg("waitpid", strerror(errno), 0), clean_exit_shell(FAILURE));
		child_count--;
		printf("PID : %d | a child is done ! (wait_child)\n", getpid());
	}
	printf("PID : %d | no more child to wait (wait_child)\n", getpid());
}

static void	__parent(t_exec_info *info)
{
	printf("PID : %d | parent\n", getpid());
	if (info->pipe_count != 0)
	{
		close(info->fd[1]);
		if (info->executed_cmd != 0)
			close(info->old_read_fd);
		info->old_read_fd = info->fd[0];
		if (info->executed_cmd == info->cmd_count - 1)
			close(info->fd[0]);
	}
	info->executed_cmd++;
}

void	solo_exit_case(t_data *d, t_exec_lst *e_lst)
{
	if (d->info->cmd_count == 1)
	{
		if (e_lst->cmd[0] != NULL && ft_strcmp(e_lst->cmd[0], "exit") == 0)
			ft_exit(e_lst->cmd);
	}
	return ;
}

static void	__before_while_cmd(t_data *d, t_exec_lst **e_lst)
{
	if (d->info->cmd_count == 1)
		execute_parent_built_in(d, e_lst->cmd);
	if (d->info->all_cmd_heredoc_nb > 16)
	{
		err_msg(NULL, ERR_MAX_HD, 0);
		clean_exit_shell(BAD_USAGE);
	}
	handle_heredoc(d, e_lst);
	return ;
}

void	while_cmd(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*curr;

	curr = *e_lst;
	__before_while_cmd(d, e_lst);
	while ((d->info->executed_cmd != d->info->cmd_count) && curr != NULL)
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
		if (d->info->child_pid == 0)
			pathfinder(d, curr, env_tab);
		else
			__parent(d->info);
		curr = curr->next;
	}
	__wait_child(d->info);
}
