/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 11:37:36 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static	void	__add_var_to_exp_env(t_env_lst **e_env, char *var)
{
	t_env_lst	*curr;
	t_env_lst	*new;

	curr = *e_env;
	new = exp_env_new_var(var);
	if (__cmp_to_equal(curr->content, new->content) > 0)
	{
		new->next = *e_env;
		*e_env = new;
		return ;
	}
	while (curr->next != NULL)
	{
		if (__cmp_to_equal(curr->next->content, new->content) > 0)
		{
			new->next = curr->next;
			curr->next = new;
			return ;
		}
		curr = curr->next;
	}
	curr->next = new;
	new->next = NULL;
}

static	void	__add_var_to_env(t_env_lst **env, char *var)
{
	t_env_lst	*curr;
	t_env_lst	*new;

	curr = *env;
	new = env_new_var(var);
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->next = NULL;
}

size_t	get_varlen(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	return (i);
}

// Si to_update a une valeur et que var n'en a pas ne pas mettre a jour
// Si 
void	update_var_val(t_env_lst *to_up, t_env_lst *to_up_exp, t_env_lst **env, char *var)
{
	if (ft_strchr(to_up_exp->content, '=') == NULL && to_up == NULL)
		__add_var_to_env(env, var);
	else if (to_up != NULL)
	{
		free(to_up->content);
		to_up->content = NULL;
		to_up->content = ft_strdup(var);
	}
	free(to_up_exp->content);
	to_up_exp->content = NULL;
	to_up_exp->content = add_quotes_to_value(var);
}

t_env_lst	*search_for_var(t_env_lst **env, char *var)
{
	t_env_lst	*curr;
	size_t		len_var;

	curr = *env;
	len_var = get_varlen(var);
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, var, len_var) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static	void	__manage_variable(t_env_lst **export_env, t_env_lst **env, char *var)
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
			__add_var_to_exp_env(export_env, var);
		else
		{
			__add_var_to_env(env, var);
			__add_var_to_exp_env(export_env, var);
		}
	}
	return ;
}

int	check_arg(char *var)
{
	int	i;

	i = 0;
	if ((ft_isalpha(var[0]) == 0 && var[0] != '_'))
		return (err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE));
	while (var[i] != '=' && var[i] != '\0')
	{
		if (ft_isalpha(var[i]) == 1
			|| ft_isdigit(var[i]) == 1 || var[i] == '_')
			i++;
		else
			return (err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE));
	}
	return (SUCCESS);
}

static	void	__print_export_env(t_env_lst **exp_env)
{
	t_env_lst    *curr;

    curr = *exp_env;
	while (curr != NULL)
	{
        ft_printf(1, "export ");
		ft_printf(1, "%s\n", curr->content);
        curr = curr->next;
  	}
}

void    my_export(t_env_lst **exp_env, t_env_lst **env, char **args)
{
	unsigned	int	i;
	
	i = 1;
	if (args[1] == NULL)
		__print_export_env(exp_env);
	else
	{
		while (args[i] != NULL)
		{
			if (check_arg(args[i]) == SUCCESS)
				__manage_variable(exp_env, env, args[i]);
			i++;
		}	
	}
}
	
//code de sortie ?
// si ajout de $WAOUH elle doit se glisser apres VTE_VERSION et
//	avant XAUTHORITY