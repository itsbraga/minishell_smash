/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:29 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/25 14:04:46 by annabrag         ###   ########.fr       */
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

void	pathfinder(t_exec_lst *node, t_redir_lst *r, t_exec_info *e_info, char **env)
{
	t_token_type	lastest_red_in;
	int				last_heredoc_fd;
	int 			error;

	error = 0;
	if (node->heredoc_nb > 0)
		last_heredoc_fd = fill_all_heredoc();
	while (r != NULL)
	{
		if (r->type == REDIR_IN || r->type == HERE_DOC)
			lastest_red_in = r->type;
		if (r->type == REDIR_IN)
			error = redirection_in(r);
		else if (r->type == REDIR_OUT_TRUNC || r->type == REDIR_OUT_APPEND)
			error = redirection_out(r);
		r = r->next;
	}
	if (lastest_red_in == HERE_DOC)
	{
		dup2(last_heredoc_fd, STDIN_FILENO);
		close(last_heredoc_fd);
	}
	go_exec(node, env);
}
