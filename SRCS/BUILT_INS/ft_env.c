/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 19:30:55 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_env_lst *env, char **args)
{
	t_env_lst	*tmp;
	t_data		*d;

	tmp = env;
	d = data_struct();
	if (args[1] != NULL)
	{
		err_msg(args[1], ERR_BAD_FILE, 1);
		d->last_exit_status = 127;
		return (d->last_exit_status);
	}
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
		tmp = tmp->next;
	}
	d->last_exit_status = SUCCESS;
	return (d->last_exit_status);
}
