/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/29 16:32:44 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	ft_exit_status(int exit_status, int mode)
{
	static int	code = 0; 
	
	if (mode == ADD)
		code = exit_status;
	if (mode == GET)
		return (code);
	return (code);
}

static char	*__append_strs(char *s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (yama(ADD, ft_strdup(s2), 0));
	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	secure_malloc(s1, true);
	(void)yama(ADD, s1, 0);
	return (s1);
}

void	err_msg(char *detail, char *reason, int quotes)
{
	char	*msg;

	msg = NULL;
	if (detail != NULL)
	{
		if (quotes == 1)
		{
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), "‘");
			msg = __append_strs(__append_strs(msg, detail), "’");
		}
		else
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), detail);
		msg = __append_strs(msg, ": ");
		msg = __append_strs(msg, reason);
	}
	else if (quotes == 2)
	{
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), ERR_PIPE);
		msg = __append_strs(__append_strs(msg, reason), "'");
	}
	else
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	yama(REMOVE, msg, 0);
}

int	err_msg_cmd(char *cmd, char *detail, char *reason, int err_status)
{
	char	*msg;

	msg = NULL;
	if (cmd != NULL)
	{
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), cmd);
		msg = __append_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __append_strs(msg, "`");
		msg = __append_strs(msg, detail);
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __append_strs(msg, "'");
		msg = __append_strs(msg, ": ");
	}
	msg = __append_strs(msg, reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	yama(REMOVE, msg, 0);
	return (err_status);
}

void	err_msg_hd(char *limiter)
{
	char	*lim_wout_newline;

	lim_wout_newline = ft_strtrim(limiter, "\n");
	ft_printf(2, "\n%swarning: here-document delimited by ", ERR_PREFIX);
	ft_printf(2, "end-of-file (wanted `%s')\n", lim_wout_newline);
	free_and_set_null(lim_wout_newline);
	return ;
}
