/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:40:43 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 03:06:51 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_env_lst	*env_new_var(char *content)
{
	t_env_lst	*new_var;

	new_var = malloc(sizeof(t_env_lst));
	secure_malloc(new_var, true);
	new_var->content = ft_strdup(content);
	secure_malloc(new_var->content, true);
	new_var->next = NULL;
	return (new_var);
}

static t_env_lst	*__env_lst_last_node(t_env_lst *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	env_lst_add_back(t_env_lst **env, t_env_lst *new_node)
{
	t_env_lst	*tmp;

	if ((*env) == NULL)
		*env = new_node;
	else
	{
		tmp = __env_lst_last_node(*env);
		tmp->next = new_node;
	}
}

void	del_env_var(t_env_lst **env, char *var_to_rm)
{
	t_env_lst	*prev;
	t_env_lst	*curr;
	int			len_var_to_rm;

	if (env == NULL || (*env) == NULL || var_to_rm == NULL)
		return ;
	prev = NULL;
	curr = *env;
	len_var_to_rm = ft_strlen(var_to_rm);
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, var_to_rm, len_var_to_rm) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free_and_set_null((void **)&curr->content);
			free_and_set_null((void **)&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
