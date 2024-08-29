/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:38:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/29 22:38:36 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

// int	my_unset(t_env *env, t_env *exp_env);
int	my_unset(t_global *g, char **args)
{
	if (args[1] == NULL)
		errmsg_exit_status("unset", args[1], FAILURE);
	else if (args != NULL)
	{
		del_env_var(&g->env, g->env);
	}
	return (SUCCESS);
}
