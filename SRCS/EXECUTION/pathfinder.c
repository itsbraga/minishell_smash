/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/03 23:23:35 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	__redirection_in(t_redir_lst *r)
{
	int	infile_fd;

	infile_fd = 0;
	infile_fd = open(r->infile, O_RDONLY);
	if (infile_fd == -1)
	{
		err_msg(r->infile, strerror(errno), 0);
		return (ft_exit_status(FAILURE, ADD));
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
		return (ft_exit_status(FAILURE, ADD));
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	return (SUCCESS);
}

static int	__handle_all_redir(t_exec_lst *node, t_token_type *latest_redin)
{
	int			error;
	t_redir_lst	*curr;

	error = 0;
	curr = node->redir;
	while (curr != NULL)
	{
		if (curr->type == REDIR_IN || curr->type == HERE_DOC)
			*latest_redin = curr->type;
		if (curr->type == REDIR_IN)
			error = __redirection_in(curr);
		else if (curr->type == REDIR_OUT_TRUNC
			|| curr->type == REDIR_OUT_APPEND)
			error = __redirection_out(curr);
		curr = curr->next;
	}
	return (error);
}

static void	__basic_behaviour(t_exec_info *info, int heredoc_nb)
{
	if (info->pipe_count != 0)
	{
		if (info->executed_cmd != (info->cmd_count - 1))
			dup2(info->fd[1], STDOUT_FILENO);
		if (info->executed_cmd != 0)
		{
			if (heredoc_nb == 0)
				dup2(info->old_read_fd, STDIN_FILENO);
			close(info->old_read_fd);
		}
		close(info->fd[1]);
		close(info->fd[0]);
	}
}

void	pathfinder(t_data *d, t_exec_lst *node)
{
	int				error;
	t_token_type	latest_redin;

	error = 0;
	latest_redin = 0;
	close_hd_other_nodes(d, node);
	__basic_behaviour(d->info, node->heredoc_nb);
	error = __handle_all_redir(node, &latest_redin);
	if (latest_redin == HERE_DOC)
		dup2(node->latest_hd, STDIN_FILENO);
	if (node->latest_hd != 0)
		close(node->latest_hd);
	if (error == FAILURE)
		clean_exit(ft_exit_status(0, GET));
	if (node->cmd == NULL)
		clean_exit(ft_exit_status(0, GET));
	else
		go_exec(node);
}
