/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:26:44 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/01 04:45:03 by pmateo           ###   ########.fr       */
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

static int	__close_heredoc(int fd[], char *line)
{
	dprintf(2, "g_sig_code = %d\n", g_sig_code);
	if (g_sig_code != CTRL_C)
	{
		free_and_set_null(line);
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		free_and_set_null(line);
		close(fd[1]);
		close(fd[0]);
		close_hd_all_nodes(data_struct());
		return (STOP_EXEC);
	}
}

static	int	__check_gnl_return(char *line, char *limiter)
{
	if (line == NULL)
	{
		if (g_sig_code == CTRL_C)
			return (FAILURE);
		else
		{
			err_msg_hd(limiter);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	open_heredoc(t_data *d, char *limiter)
{
	int		fd[2];
	bool	must_expand;
	char	*line;
	char	*line_w_nl;

	if (pipe(fd) == -1)
	{
		err_msg("pipe", strerror(errno), 0);
		clean_exit_shell(FAILURE);
	}
	must_expand = __manage_limiter(&limiter);
	while (1)
	{
		line = readline("> ");
		if (__check_gnl_return(line, limiter) == FAILURE)
			break ;
		if (ft_strcmp(limiter, line) == 0)
			break ;
		if (must_expand == true)
			line = expand(d, line, true);
		line_w_nl = ft_strjoin(line, "\n");
		secure_malloc(line_w_nl, true);
		(ft_printf(fd[1], "%s", line_w_nl), free_and_set_null(line));
	}
	return (__close_heredoc(fd, line));
}
