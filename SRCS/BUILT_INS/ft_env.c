/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/24 21:01:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_env_lst *env, char **args)
{
	t_env_lst	*tmp;

	tmp = env;
	if (args[1] != NULL)
	{
		err_msg(args[1], ERR_BAD_FILE, 1);
		return (ft_exit_status(CMD_NOT_FOUND, ADD));
	}
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (ft_exit_status(SUCCESS, ADD));
}
