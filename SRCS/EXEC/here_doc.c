/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/28 01:03:31 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

static bool	__manage_limiter(char **limiter)
{
	if (ft_strchr(*limiter, '"') == NULL || ft_strchr(*limiter, '\'') == NULL)
		return (true);
	else
	{
		*limiter = empty_quotes(*limiter);
		*limiter = other_quotes(*limiter);
		return (false);
	}
}

static int		__close_heredoc(int fd[], char *limiter, char *buffer)
{
	get_next_line(0, 1);
	free(buffer);
	buffer = NULL;
	free(limiter);
	close(fd[1]);
	return(fd[0]);
}

static int		__open_heredoc(t_data *d, char *limiter)
{
	int		fd[2];
	bool	must_expand;
	char 	*buffer;

	buffer = NULL;
	if (pipe(fd) == -1)
	{
		err_msg(NULL, strerror(errno), 0);
		clean_exit_shell(FAILURE);
	}
	must_expand = __manage_limiter(&limiter);
	while (1)
	{
		ft_printf(2, "> ");
		buffer = get_next_line(0, 0);
		if (!buffer)
			break;
		if (ft_strcmp(limiter, buffer) == 0)
			break;
		if (must_expand == true)
			buffer = expand(d, buffer, true);
		ft_printf(fd[1], "%s", buffer);
		free(buffer);
	}
	return (__close_heredoc(fd, limiter, buffer));
}

int	fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	t_redir_lst *node;
	int			latest_read_fd;
	char		*tmp;

	node = r;
	latest_read_fd = 0;
	tmp = NULL;
	while (node != NULL)
	{
		if (node->type == HERE_DOC)
		{
			tmp = node->limiter;
			node->limiter = ft_strjoin(node->limiter, "\n");
			yama(REMOVE, tmp, 0);
			latest_read_fd = __open_heredoc(d, node->limiter);
		}
		node = node->next;
	}
	return (latest_read_fd);
}
