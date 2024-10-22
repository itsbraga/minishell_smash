/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:03:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 23:46:48 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	add_var_to_exp_env(t_env_lst *e_env, char *var)
{
	t_env_lst	*current;
	t_env_lst	*new;

	current = e_env;
	new = exp_env_new_var(var);
	if (cmp_to_equal(current->content, new->content) > 0)
	{
		new->next = current;
		e_env = new;
		return ;
	}
	while (current->next != NULL)
	{
		if (cmp_to_equal(current->next->content, new->content) > 0)
		{
			new->next = current->next;
			current->next = new;
			return ;
		}
		current = current->next;
	}
	current->next = new;
	new->next = NULL;
}

void	add_var_to_env(t_env_lst *env, char *var)
{
	t_env_lst	*current;
	t_env_lst	*new;

	current = env;
	new = env_new_var(var);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->next = NULL;
}

static size_t   __get_varlen(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	return (i);
}

void	update_var_val(t_env_lst *to_up, t_env_lst *to_up_exp,
t_env_lst *env, char *var)
{
	if ((ft_strchr(to_up_exp->content, '=') == NULL) && to_up == NULL)
		add_var_to_env(env, var);
	else if (to_up != NULL)
	{
		free_and_set_null(to_up->content);
		to_up->content = ft_strdup(var);
	}
	free_and_set_null(to_up_exp->content);
	to_up_exp->content = add_quotes_to_value(var);
}

t_env_lst	*search_for_var(t_env_lst *env, char *var)
{
	t_env_lst	*current;
	size_t		len_var;

	current = env;
	len_var = __get_varlen(var);
	while (current != NULL)
	{
		if (ft_strncmp(current->content, var, len_var) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
