/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:26:44 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/30 20:45:06 by pmateo           ###   ########.fr       */
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
void		__sigint_close_heredoc(int *fd, char *line, char *limiter)
{
	dprintf(2, "PID : %d | closehd | cc\n", getpid());
	get_next_line(0, 1);
	free_and_set_null(line);
	free_and_set_null(limiter);
	close(fd[0]);
	close(fd[1]);
	clean_exit_shell(ft_exit_status(0, GET));
}

static	int	__check_gnl_return(char *line, char *limiter)
{
	if (line == NULL && g_sig_code != CTRL_C)
	{
		err_msg_hd(limiter);
		return (FAILURE);
	}
	else
		return (SUCCESS);
}

int	open_heredoc(t_data *d, char *limiter)
{
	int		fd[2];
	bool	must_expand;
	char	*line;

	line = NULL;
	if (pipe(fd) == -1)
	{
		err_msg(NULL, strerror(errno), 0);
		exit(FAILURE);
	}
	must_expand = __manage_limiter(&limiter);
	set_signals_in_heredoc();
	while (1)
	{
		ft_printf(2, "> ");
		line = get_next_line(0, 0);
		//if (g_sig_code == CTRL_C)
		if (g_sig_code == 4)
			__sigint_close_heredoc(fd, line, limiter);
		if (__check_gnl_return(line, limiter) == FAILURE)
			break;
		if (ft_strcmp(limiter, line) == 0)
			break ;
		if (must_expand == true)
			line = expand(d, line, true);
		ft_printf(fd[1], "%s", line);
		free_and_set_null(line);
	}
	return (__close_heredoc(fd, limiter, line));
}
