/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/11 03:13:58 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envlst_size(t_env_lst **env)
{
	size_t		size;
	t_env_lst	*current;

	size = 0;
	current = *env;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

size_t	get_envtab_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size] != NULL)
		size++;
	return (size);
}

t_env_lst	*env_new_var(char *content)
{
	t_env_lst	*new_var;

	new_var = yama(CREATE, NULL, sizeof(t_env_lst));
	secure_malloc(new_var);
	new_var->content = ft_strdup(content);
	secure_malloc(new_var->content);
	(void)yama(ADD, new_var->content, 0);
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

char	**recreate_env_tab(t_env_lst **env)
{
	char		**tab;
	t_env_lst	*current;
	int			i;

	// tab = malloc(sizeof(char *) * get_envlst_size(env));
	// secure_malloc(tab);
	tab = yama(CREATE_TAB, NULL, (sizeof(char *) * (get_envlst_size(env) + 1)));
	secure_malloc(tab);
	current = *env;
	i = 0;
	while (current != NULL)
	{
		// tab[i] = ft_strdup(current->content);
		// secure_malloc(tab[i]);
		// (void)yama(ADD, tab[i], 0);
		tab[i] = current->content;
		i++;
		current = current->next;
	}
	tab[i] = NULL;
	return (tab);
}
