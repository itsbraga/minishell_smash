/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/23 15:44:28 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		open_heredoc(char *limiter)
{
	int	fd[2];
	char *buffer;

	buffer = NULL;
	if (pipe(fd) == -1)
	{
		err_msg(NULL, strerror(errno), 0);
		clean_exit_shell(1);
	}
	while (1)
	{
		ft_printf(2, "> ");
		buffer = get_next_line(0, 0);
		if (!buffer)
			break;
		if (ft_strcmp(limiter, buffer) == 0)
			break;
		ft_printf(fd[1], "%s", buffer);
		free(buffer);
	}
	get_next_line(0, 1);
	free(buffer);
	buffer = NULL;
	free(limiter);
	return (close(fd[1]), fd[0]);
}

int	fill_all_heredoc(t_redir_lst *r)
{
	t_redir_lst *node;
	int			lastest_read_fd;
	char		*tmp;

	node = r;
	lastest_read_fd = 0;
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
