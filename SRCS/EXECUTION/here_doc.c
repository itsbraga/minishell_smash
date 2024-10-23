/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 22:43:45 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static int	__close_heredoc(int fd[], char *limiter, char *line)
{
	get_next_line(0, 1);
	free_and_set_null(line);
	free_and_set_null(limiter);
	close(fd[1]);
	return (fd[0]);
}

static int	__open_heredoc(t_data *d, char *limiter)
{
	int		fd[2];
	bool	must_expand;
	char	*line;

	line = NULL;
	if (pipe(fd) == -1)
		(err_msg(NULL, strerror(errno), 0), exit(FAILURE));
	must_expand = __manage_limiter(&limiter);
	// signal(SIGINT, set_signals_in_heredoc);
	while (1)
	{
		ft_printf(2, "> ");
		line = get_next_line(0, 0);
		dprintf(2, "before heredoc gnl | line = %s\n", line);
		if (line == NULL)
			break ;
		if (ft_strcmp(limiter, line) == 0)
			break ;
		if (must_expand == true)
			line = expand(d, line, true);
		ft_printf(fd[1], "%s", line);
		free_and_set_null(line);
	}
	return (__close_heredoc(fd, limiter, line));
}

int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	t_redir_lst	*curr;
	char		*tmp;
	int			latest_read_fd;

	curr = r;
	tmp = NULL;
	latest_read_fd = 0;
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC)
		{
			tmp = curr->limiter;
			curr->limiter = ft_strjoin(curr->limiter, "\n");
			secure_malloc(curr->limiter, true);
			free_and_set_null(tmp);
			latest_read_fd = __open_heredoc(d, curr->limiter);
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
