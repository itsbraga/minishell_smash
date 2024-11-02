/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 02:21:50 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_env_lst **env, char **args)
{
	t_env_lst	*curr;

	curr = *env;
	if (args[1] != NULL)
	{
		if (*args[1] == '-')
			err_msg(args[1] + 1, ERR_BAD_FILE, 1);
		else
			err_msg(args[1], ERR_BAD_FILE, 1);
		return (ft_exit_status(CMD_NOT_FOUND, ADD));
	}
	while (curr != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", curr->content);
		curr = curr->next;
	}
	return (ft_exit_status(SUCCESS, ADD));
}
