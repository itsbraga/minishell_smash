/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/14 02:58:55 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static	void	__add_variable(t_env_lst *env, char *var)
{
	
}

static	void	__handle_args(t_env_lst *exp_env, char **args)
{
	unsigned	int	i;
	
	i = 0;
	while (args[i] != NULL)
	{
		if (check_arg() == SUCCESS)
			add_variable();
		i++;
	}
}

static	void	__print_export_env(t_env_lst *exp_env)
{
	t_env_lst    *curr;

    curr = exp_env;
	while (curr != NULL)
	{
        ft_printf(1, "export ");
		ft_printf(1, "%s\n", curr->content);
        curr = curr->next;
  	}
}

void    my_export(t_env_lst *exp_env, char **args)
{
	if (args[1] == NULL)
		__print_export_env(exp_env);
	else
		__handle_args(exp_env, args);
	
//code de sortie ?