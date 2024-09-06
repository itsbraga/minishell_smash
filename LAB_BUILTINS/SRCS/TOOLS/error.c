/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/06 01:29:55 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static char	*__combine_and_free_strs(char *s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	tmp = NULL;
	return (s1);
}

void	err_msg(char *detail, char *reason)
{
	char	*msg;

	msg = __combine_and_free_strs(ERR_PREFIX, detail);
	msg = __combine_and_free_strs(msg, ": ");
	msg = __combine_and_free_strs(msg, reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	msg = NULL;
}

int	err_msg_cmd(char *cmd, char *detail, char *reason, int err_status)
{
	char	*msg;
	
	if (cmd != NULL)
	{
		msg = __combine_and_free_strs(ERR_PREFIX, cmd);
		msg = __combine_and_free_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __combine_and_free_strs(msg, "`");
		msg = __combine_and_free_strs(msg, detail);
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __combine_and_free_strs(msg, "'");
		msg = __combine_and_free_strs(msg, ": ");
	}
	msg = __combine_and_free_strs(msg, reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (err_status);
}
