/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:38:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 11:47:39 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int	my_unset(t_global *g, char **args)
{
	int		i;

	i = 1;
	while (args[i] != NULL)
	{
		del_env_var(g->env, args[i]);
		del_env_var(g->exp_env, args[i]);
		i++;
	}
	// g->last_exit_status = 0;
	return (SUCCESS);
}
