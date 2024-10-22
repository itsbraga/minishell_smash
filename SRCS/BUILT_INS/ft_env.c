/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 20:43:36 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_env_lst *env)
{
	t_env_lst	*tmp;
	t_data		*d;

	tmp = env;
	d = data_struct();
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (d->last_exit_status = SUCCESS);
}
