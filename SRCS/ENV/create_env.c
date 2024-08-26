/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 16:06:39 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new_var(char *content)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	new_var->content = ft_strdup(content);
	new_var->next = NULL;
	return (new_var);
}

void	lstclear_env(t_env **env)
{
    t_env *tmp;

    if (env == NULL || (*env) == NULL)
        return ;
    while ((*env) != NULL)
    {
        tmp = (*env)->next;
        free((*env)->content);
        free(*env);
        *env = tmp;
    }
}

int	create_env_list(t_env **env, char **envp)
{
	int		i;
	t_env	*var;
	t_env	*last;

	i = 0;
	if (env == NULL || envp == NULL)
		return (FAILURE);
	*env = NULL;
	last = NULL;
	while (envp[i] != NULL)
	{
		var = env_new_var(envp[i]);
		if (var == NULL)
		{
			lstclear_env(env);
			return (FAILURE);
		}
		if (last != NULL)
			last->next = var;
		else
			*env = var;
		last = var;
		i++;
	}
	return (SUCCESS);
}
