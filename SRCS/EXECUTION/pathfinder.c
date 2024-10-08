/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 17:03:23 by pmateo           ###   ########.fr       */
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
	int flags;

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
		else if (node->redir->type == REDIR_OUT_TRUNC ||
					node->redir->type == REDIR_OUT_APPEND)
			error = __redirection_out(node->redir);
		node->redir = node->redir->next;
	}
	return (error);
}

static	void	__basic_behaviour(t_exec_info *info)
{
	if (info->executed_cmd != 0)
	{
		dup2(info->old_read_fd, STDIN_FILENO);
		close(info->old_read_fd);
	}
	if (info->executed_cmd != (info->cmd_count - 1))
		dup2(info->fd[1], STDOUT_FILENO);
	close(info->fd[1]);
	close(info->fd[0]);
}

void	pathfinder(t_data *d, t_exec_lst *node, char **env)
{
	int 			error;
	int				last_heredoc_fd;
	t_token_type	latest_redin;

	error = 0;
	last_heredoc_fd = 0;
	latest_redin = 0;
	printf("debut pathfinder\n");
	__basic_behaviour(d->info);
	if (node->heredoc_nb > 0)
		last_heredoc_fd = fill_all_heredoc(d, node->redir);
	error = __handle_all_redir(node, &latest_redin);
	if (latest_redin == HERE_DOC)
	{
		dup2(last_heredoc_fd, STDIN_FILENO);
		close(last_heredoc_fd);
	}
	if (error == FAILURE)
		return ;
	else
		go_exec(node, env);
}
