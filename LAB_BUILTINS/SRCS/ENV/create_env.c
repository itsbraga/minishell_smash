/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/06 01:22:19 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

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

int	create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size, 
	size_t idx_exp_env)
{
	t_env	*to_add;
	t_env	*last;

	to_add = NULL;
	last = NULL;
	while (idx_exp_env != envp_size)
	{
		if (idx_exp_env == 0)
			to_add = copy_toppest(envp);
		else
			to_add = ascii_sort(envp, last->content);
		if (to_add == NULL)
		{
			lstclear_env(exp_env);
			return (FAILURE);
		}
		if (last == NULL)
			*exp_env = to_add;
		else
			last->next = to_add;
		last = to_add;
		idx_exp_env++;
	}
	return (SUCCESS);
}

void	create_env(t_global *g, char **envp)
{
	size_t	envp_size;

	envp_size = get_env_size(envp);
	if (create_env_list(&g->env, envp) == FAILURE)
		err_msg("An error occured with env_list", NULL);
	if (create_exp_env_list(&g->exp_env, envp, envp_size, 0) == FAILURE)
		err_msg("An error occured with export_env_list", NULL);
}
