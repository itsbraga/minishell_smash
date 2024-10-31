/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:26:44 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/31 10:57:05 by annabrag         ###   ########.fr       */
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
	if (g_sig_code != CTRL_C)
	{
		get_next_line(0, 1);
		free_and_set_null(line);
		free_and_set_null(limiter);
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		get_next_line(0, 1);
		free_and_set_null(line);
		free_and_set_null(limiter);
		close(fd[1]);
		close(fd[0]);
		return (STOP_EXEC);
	}
}
// void		__sigint_close_heredoc(int *fd, char *line, char *limiter)
// {
// 	dprintf(2, "PID : %d | closehd | cc\n", getpid());
// 	get_next_line(0, 1);
// 	free_and_set_null(line);
// 	free_and_set_null(limiter);
// 	close(fd[0]);
// 	close(fd[1]);
// }

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

	line = NULL;
	if (pipe(fd) == -1)
	{
		err_msg("pipe", strerror(errno), 0);
		clean_exit_shell(FAILURE);
	}
	must_expand = __manage_limiter(&limiter);
	while (1)
	{
		// ft_printf(2, "> ");
		// line = get_next_line(0, 0);
		line = readline("> ");
		// //if (g_sig_code == CTRL_C)
		// if (g_sig_code == 4)
		// 	__sigint_close_heredoc(fd, line, limiter);
		if (__check_gnl_return(line, limiter) == FAILURE)
			break;
		if (ft_strcmp(limiter, line) == 0)
			break ;
		if (must_expand == true)
			line = expand(d, line, true);
		// ft_printf(fd[1], "%s", line);
		free_and_set_null(line);
	}
	return (__close_heredoc(fd, limiter, line));
}
