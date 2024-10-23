/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 20:08:44 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t	get_envlst_size(t_env_lst **env)
{
	size_t		size;
	t_env_lst	*curr;

	size = 0;
	curr = *env;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
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
		if ((ft_strncmp(curr->content, var_to_rm, len_var_to_rm) == 0)
			&& (curr->content[len_var_to_rm] == '='))
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free_and_set_null(curr->content);
			free_and_set_null(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

char	**recreate_env_tab(t_env_lst **env)
{
	char		**tab;
	t_env_lst	*curr;
	int			i;

	tab = yama(CREATE_TAB, NULL, (sizeof(char *) * (get_envlst_size(env) + 1)));
	secure_malloc(tab, true);
	curr = *env;
	i = 0;
	while (curr != NULL)
	{
		tab[i] = ft_strdup(curr->content);
		secure_malloc(tab[i], true);
		(void)yama(ADD, tab[i], 0);
		i++;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}
