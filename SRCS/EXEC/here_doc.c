/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/22 17:23:18 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		open_heredoc()
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		err_msg(NULL, strerror(errno), 0);
		clean_exit_shell(1);
	}
	
}

void	fill_all_heredoc(t_redir_lst *r)
{
	t_redir_lst *node;
	int			lastest_read_fd;
	char		*tmp;

	node = r;
	read_fd = 0;
	tmp = NULL;
	while (node != NULL)
	{
		if (node->type == HERE_DOC)
		{
			tmp = node->limiter;
			node->limiter = ft_strjoin(node->limiter, "\n");
			yama(REMOVE, tmp, 0);
			lastest_read_fd = open_heredoc(node->limiter);
		}
		node == node->next;
	}
	return (lastest_read_fd);
}
