/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/29 02:27:47 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	t_redir_lst	*curr;
	char		*limiter_w_newline;
	int			latest_read_fd;

	curr = r;
	limiter_w_newline = NULL;
	latest_read_fd = 0;
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC)
		{
			if (latest_read_fd != 0)
				close(latest_read_fd);
			limiter_w_newline = ft_strjoin(curr->limiter, "\n");
			secure_malloc(curr->limiter, true);
			latest_read_fd = open_heredoc(d, limiter_w_newline);
		}
		curr = curr->next;
	}
	return (latest_read_fd);
}

void	handle_heredoc(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*curr;

	curr = *e_lst;
	while (curr != NULL)
	{
		if (curr->heredoc_nb > 0)
			curr->latest_hd = __fill_all_heredoc(d, curr->redir);
		curr = curr->next;
	}
	return ;
}
