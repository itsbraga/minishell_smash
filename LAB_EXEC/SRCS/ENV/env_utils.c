/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/01 07:15:01 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/mini_exec.h"

static size_t	get_envlst_size(t_env_lst *env)
{
	size_t	size;
	
	size = 0;
	while (env != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**recreate_env_tab(t_env_lst **env)
{
	char		**tab;
	t_env_lst 	*node;
	int			i;

	tab = malloc(get_envlst_size(env) * sizeof(char *));
	node = *env;
	i = 0;
	while (node != NULL)
	{
		tab[i] = ft_strdup(node->content);
		i++;
		node = node->next;
	}
	return (tab);
}

t_env_lst	*env_new_var(char *content, bool is export)
{
	t_env_lst	*new_var;

	new_var = malloc(sizeof(t_env_lst));
	if (new_var == NULL)
		return (NULL);
	new_var->content = ft_strdup(content);
	if (new_var->content == NULL)
	{
		free(new_var);
		return (NULL);
	}
	new_var->next = NULL;
	return (new_var);
}

void	del_env_var(t_env_lst **env, char *var_to_rm)
{
	t_env_lst	*prev;
	t_env_lst	*current;
	int			len_var_to_rm;

	if (env == NULL || (*env) == NULL || var_to_rm == NULL)
		return ;
	prev = NULL;
	current = *env;
	len_var_to_rm = ft_strlen(var_to_rm);
    while (current != NULL)
    {
        if ((ft_strncmp(current->content, var_to_rm, len_var_to_rm) == 0)
				&& (current->content[len_var_to_rm] == '='))
        {
            if (prev == NULL)
                *env = current->next; // Si le node à supprimer est le premier de la liste
            else
                prev->next = current->next; // Si le node à supprimer est au milieu ou à la fin
            free(current->content);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}
