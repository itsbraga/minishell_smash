/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/27 21:36:22 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in(t_redir_lst *r)
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

int	redirection_out(t_redir_lst *r)
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

void	pathfinder(t_data *d, t_exec_lst *node, char **env)
{
	t_token_type	lastest_red_in;
	int				last_heredoc_fd;
	int 			error;

	error = 0;
	if (node->heredoc_nb > 0)
		last_heredoc_fd = fill_all_heredoc(d, node->redir);
	while (node->redir != NULL)
	{
		if (node->redir->type == REDIR_IN || node->redir->type == HERE_DOC)
			lastest_red_in = node->redir->type;
		if (node->redir->type == REDIR_IN)
			error = redirection_in(node->redir);
		else if (node->redir->type == REDIR_OUT_TRUNC ||
								node->redir->type == REDIR_OUT_APPEND)
			error = redirection_out(node->redir);
		node->redir = node->redir->next;
	}
	if (lastest_red_in == HERE_DOC)
	{
		dup2(last_heredoc_fd, STDIN_FILENO);
		close(last_heredoc_fd);
	}
	go_exec(node, env);
}
