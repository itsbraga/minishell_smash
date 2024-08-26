/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 19:11:51 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 16:06:39 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
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

<<<<<<< HEAD
void lstclear_env(t_env **env)
=======
void	lstclear_env(t_env **env)
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
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
<<<<<<< HEAD
=======

>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
int	create_env_list(t_env **env, char **envp)
{
	int		i;
	t_env	*var;
	t_env	*last;

	i = 0;
<<<<<<< HEAD
	if (envp == NULL)
		return (EXIT_FAILURE);
=======
	if (env == NULL || envp == NULL)
		return (FAILURE);
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
	*env = NULL;
	last = NULL;
	while (envp[i] != NULL)
	{
		var = env_new_var(envp[i]);
		if (var == NULL)
		{
			lstclear_env(env);
<<<<<<< HEAD
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
 
=======
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
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
