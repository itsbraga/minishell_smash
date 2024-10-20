/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/20 21:09:55 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__redirection_in(t_redir_lst *r)
{
	int	infile_fd;

	infile_fd = 0;
	infile_fd = open(r->infile, O_RDONLY);
	if (infile_fd == -1)
	{
		err_msg(r->infile, strerror(errno), 0);
		return (FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	return (SUCCESS);
}

static int	__redirection_out(t_redir_lst *r)
{
	int	outfile_fd;
	int	flags;

	outfile_fd = 0;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (r->type == REDIR_OUT_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	outfile_fd = open(r->outfile, flags, 0755);
	if (outfile_fd == -1)
	{
		err_msg(r->outfile, strerror(errno), 0);
		return (FAILURE);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	return (SUCCESS);
}

static	int	__handle_all_redir(t_exec_lst *node, t_token_type *latest_redin)
{
	int				error;

	error = 0;
	while (node->redir != NULL)
	{
		if (node->redir->type == REDIR_IN || node->redir->type == HERE_DOC)
			*latest_redin = node->redir->type;
		if (node->redir->type == REDIR_IN)
			error = __redirection_in(node->redir);
		else if (node->redir->type == REDIR_OUT_TRUNC
			|| node->redir->type == REDIR_OUT_APPEND)
			error = __redirection_out(node->redir);
		node->redir = node->redir->next;
	}
	return (error);
}

static	void	__basic_behaviour(t_exec_info *info, int heredoc_nb)
{
	dprintf(2, "PID : %d | executed_cmd (basic_behaviour) = %d\n", getpid(), info->executed_cmd);
	// info->stdin_backup = dup(STDIN_FILENO);
	// if (isatty(info->stdin_backup) == 1)
	// 		dprintf(2, "PID : %d | FD(stdinbackup) lit sur STDIN :)\n", getpid());
	// else
	// 		dprintf(2, "PID : %d | FD(stdinbackup) ne lit pas sur STDIN /!\\\n", getpid());
	// get_next_line(info->stdin_backup, 0);
	//  dprintf(2, "PID : %d | dup2 a échoué: %s\n", getpid(), strerror(errno));
	if (info->pipe_count != 0)
	{
		if (info->executed_cmd != (info->cmd_count - 1))
		{
			dup2(info->fd[1], STDOUT_FILENO);
			dprintf(2, "PID : %d | FD(%d) à été trompé et écrit au même endroit que FD(%d)\n", getpid(), STDOUT_FILENO, info->fd[1]);
		}
		if (info->executed_cmd != 0)
		{
			// dprintf(2, "GNL : %s\n", get_next_line(info->old_read_fd, 0));
			// dup2(info->old_read_fd, STDIN_FILENO);
			// dprintf(2, "PID : %d | FD(%d) à été trompé et lit au même endroit que FD(%d)\n", getpid(), STDIN_FILENO, info->old_read_fd);
			if (heredoc_nb == 0)
				dup2(info->old_read_fd, STDIN_FILENO);
			close(info->old_read_fd);
			// dprintf(2, "PID : %d | FD(%d) à été fermé\n", getpid(), info->old_read_fd);
		}
		// dprintf(2, "PID : %d | executed_cmd : %d ; cmd_count : %d\n", getpid(), info->executed_cmd, info->cmd_count);
		close(info->fd[1]);
		// dprintf(2, "PID : %d | FD(%d) à été fermé\n", getpid(), info->fd[1]);
		close(info->fd[0]);
		// dprintf(2, "PID : %d | FD(%d) à été fermé\n", getpid(), info->fd[0]);
	}
} 

void	pathfinder(t_data *d, t_exec_lst *node, char **env)
{
	int				error;
	t_token_type	latest_redin;

	error = 0;
	latest_redin = 0;
	dprintf(2, "debut pathfinder\n");
	dprintf(2, "PID : %d | cmd[0] = %s\n", getpid(), node->cmd[0]);
	__basic_behaviour(d->info, node->heredoc_nb);
	error = __handle_all_redir(node, &latest_redin);
	if (latest_redin == HERE_DOC)
	{
		dup2(node->latest_hd, STDIN_FILENO);
		close(node->latest_hd);
	}
	if (error == FAILURE)
		exit (FAILURE); // cause des leaks
	else
		go_exec(node, env);
}

// ls | cat
// STDIN -> ls -> dup2(fd[1], STDOUT)
// dup2(old-read-fd, STDIN) -> cat -> STDOUT
