/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 19:11:51 by pmateo           ###   ########.fr       */
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

void lstclear_env(t_env **env)
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
	if (envp == NULL)
		return (EXIT_FAILURE);
	*env = NULL;
	last = NULL;
	while (envp[i] != NULL)
	{
		var = env_new_var(envp[i]);
		if (var == NULL)
		{
			lstclear_env(env);
			return (EXIT_FAILURE);
		}
		if (last == NULL)
			*env = var;
		else
			last->next = var;
		last = var;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	create_env(t_global *g, char **envp)
{
	size_t	envp_size;

	envp_size = get_env_size(envp);
	if (create_env_list(&g->env, envp) == EXIT_FAILURE)
		ft_printf(1, "ERROR OCCURED WITH ENV_LIST\n");
	if (create_exp_env_list(&g->exp_env, envp, envp_size, 0) == EXIT_FAILURE)
		ft_printf(1, "ERROR OCCURED WITH EXPORT ENV_LIST\n");
	return ;
}
 