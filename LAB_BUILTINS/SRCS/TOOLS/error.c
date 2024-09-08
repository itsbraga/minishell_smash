/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/08 22:46:03 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

/// @ GROOOOOOOOOS LEAKS ICI 
static char	*__combine_and_free_strs(char *s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	if (s1 == NULL)
		return (NULL);
	return (s1);
}

void	err_msg(char *detail, char *reason, int quotes)
{
	char	*msg;

	if (detail != NULL)
	{
		if (quotes == 1)
		{
			msg = __combine_and_free_strs(ERR_PREFIX,"‘");
			msg = __combine_and_free_strs(msg, detail);
			msg = __combine_and_free_strs(msg, "’");
		}
		else
			msg = __combine_and_free_strs(ERR_PREFIX, detail);
		msg = __combine_and_free_strs(msg, ": ");
		msg = __combine_and_free_strs(msg, reason);
	}
	else
		msg = __combine_and_free_strs(ERR_PREFIX, reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
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
