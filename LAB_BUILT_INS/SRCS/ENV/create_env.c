/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 16:17:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

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

int	create_env_list(t_env **env, char **envp)
{
	int		i;
	t_env	*var;
	t_env	*last;

	i = 0;
	if (envp == NULL)
		return (FAILURE);
	var = NULL;
	last = NULL;
	while (envp[i] != NULL)
	{
		var = env_new_var(envp[i]);
		if (var == NULL)
		{
			lstclear_env(env);
			return (FAILURE);
		}
		if (last == NULL)
			*env = var;
		else
			last->next = var;
		last = var;
		i++;
	}
	return (SUCCESS);
}
