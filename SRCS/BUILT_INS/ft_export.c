/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 21:01:01 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	__manage_variable(t_env_lst **export_env, t_env_lst **env,
char *var)
{
	t_env_lst	*to_find;
	t_env_lst	*to_find_exp;

	to_find = search_for_var(env, var);
	to_find_exp = search_for_var(export_env, var);
	if (to_find_exp != NULL && ft_strchr(var, '=') != NULL)
		update_var_val(to_find, to_find_exp, env, var);
	else if (to_find_exp == NULL)
	{
		if (ft_strchr(var, '=') == NULL)
			add_var_to_exp_env(export_env, var);
		else
		{
			add_var_to_env(env, var);
			add_var_to_exp_env(export_env, var);
		}
	}
}

static int	__check_args(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
	{
		err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE);
		return (ft_exit_status(FAILURE, ADD));
	}
	else
		i++;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (ft_isalpha(var[i]) == 1 || ft_isdigit(var[i]) == 1 || var[i] == '_')
			i++;
		else
		{
			err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE);
			return (ft_exit_status(FAILURE, ADD));
		}
	}
	return (ft_exit_status(SUCCESS, ADD));
}

static void	__print_export_env(t_env_lst **exp_env)
{
	t_env_lst	*curr;

	curr = *exp_env;
	while (curr != NULL)
	{
		ft_printf(STDOUT_FILENO, "export %s\n", curr->content);
		curr = curr->next;
	}
}

int	ft_export(t_env_lst **exp_env, t_env_lst **env, char **args)
{
	unsigned int	i;

	i = 1;
	if (args[1] == NULL)
		__print_export_env(exp_env);
	else
	{
		while (args[i] != NULL)
		{
			if (__check_args(args[i]) == SUCCESS)
				__manage_variable(exp_env, env, args[i]);
			i++;
		}
	}
	return (ft_exit_status(0, GET));
}
