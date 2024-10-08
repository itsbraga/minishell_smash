/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/08 17:03:06 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
		tmp = tmp->next;
	}
	// data_struct()->last_exit_status = 0;
	return (SUCCESS);
}
