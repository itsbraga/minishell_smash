/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:38:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/04 18:43:20 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(t_global *g, char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		del_env_var(&g->env, args[i]);
		del_env_var(&g->exp_env, args[i]);
		i++;
	}
	g->last_exit_status = 0;
	return (SUCCESS);
}
