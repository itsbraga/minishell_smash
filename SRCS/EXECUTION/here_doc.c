/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 02:33:37 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	__close_heredoc(int fd[], char *limiter, char *buffer)
{
	get_next_line(0, 1);
	free(buffer);
	buffer = NULL;
	free(limiter);
	close(fd[1]);
	return (fd[0]);
}

static int	__open_heredoc(t_data *d, char *limiter)
{
	int		fd[2];
	bool	must_expand;
	char	*buffer;

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
		buffer = get_next_line(0, 0); // readline ?
		dprintf(2, "before heredoc gnl | buffer = %s\n", buffer);
		if (buffer == NULL)
			break ;
		if (ft_strcmp(limiter, buffer) == 0)
			break ;
		if (must_expand == true)
			buffer = expand(d, buffer, true);
		ft_printf(fd[1], "%s", buffer);
		free(buffer);
	}
	return (__close_heredoc(fd, limiter, buffer));
}

int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	t_redir_lst	*current;
	char		*tmp;
	int			latest_read_fd;

	current = r;
	tmp = NULL;
	latest_read_fd = 0;
	while (current != NULL)
	{
		if (current->type == HERE_DOC)
		{
			tmp = current->limiter;
			current->limiter = ft_strjoin(current->limiter, "\n");
			secure_malloc(current->limiter, true);
			yama(REMOVE, tmp, 0);
			latest_read_fd = __open_heredoc(d, current->limiter);
		}
		current = current->next;
	}
	return (latest_read_fd);
}

void	handle_heredoc(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*current;
	int	i; i = 1;

	current = *e_lst;
	while (current != NULL)
	{
		if (current->heredoc_nb > 0)
			current->latest_hd = __fill_all_heredoc(d, current->redir);
		current = current->next;
	}
	return ;
}
