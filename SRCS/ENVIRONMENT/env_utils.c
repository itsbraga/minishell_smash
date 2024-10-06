/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/06 22:05:12 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// char	**recreate_env_tab(t_env_lst **env)
// {
// 	char		**tab;
// 	t_env_lst 	*node;
// 	int			i;

// 	tab = malloc(get_env_size(env) * sizeof(char *));
// 	node = *env;
// 	i = 0;
// 	while (node != NULL)
// 	{
// 		tab[i] = ft_strdup(node->content);
// 		i++;
// 		node = node->next;
// 	}
// 	return (tab);
// }
