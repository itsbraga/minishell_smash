/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:03:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 03:03:49 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	add_var_to_exp_env(t_env_lst **e_env, char *var)
{
	t_env_lst	*curr;
	t_env_lst	*new;

	curr = *e_env;
	new = exp_env_new_var(var);
	if (cmp_to_equal((*e_env)->content, new->content) > 0)
	{
		new->next = *e_env;
		*e_env = new;
		return ;
	}
	while (curr->next != NULL)
	{
		if (cmp_to_equal(curr->next->content, new->content) > 0)
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

void	add_var_to_env(t_env_lst **env, char *var)
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

static size_t	__get_varlen(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	return (i);
}

void	update_var_val(t_env_lst *to_up, t_env_lst *to_up_exp, t_env_lst **env,
char *var)
{
	if (to_up == NULL && ft_strchr(to_up_exp->content, '=') == NULL)
		add_var_to_env(env, var);
	else if (to_up != NULL)
	{
		free_and_set_null((void **)&to_up->content);
		to_up->content = ft_strdup(var);
		secure_malloc(to_up->content, true);
	}
	free_and_set_null((void **)&to_up_exp->content);
	to_up_exp->content = add_quotes_to_value(var);
	secure_malloc(to_up_exp->content, true);
}

t_env_lst	*search_for_var(t_env_lst **env, char *var)
{
	t_env_lst	*curr;
	size_t		len_var;

	curr = *env;
	len_var = __get_varlen(var);
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, var, len_var) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
