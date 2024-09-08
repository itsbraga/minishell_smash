/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/08 21:52:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	__update_shlvl(t_env *env)
{
	t_env	*head;
	int		var_value;
	char	*new_value;

	head = env;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, "SHLVL=", 6) == 0)
		{
			var_value = ft_atoi(head->content + 6, 0);
			var_value += 1;
			new_value = ft_itoa(var_value);
			free(head->content);
			head->content = ft_strjoin("SHLVL=", new_value);
			if (head->content == NULL)
				return ;
			free(new_value);
		}
		head = head->next;
	}
}

void	create_env(t_global *g, char **envp)
{
	size_t	envp_size;

	envp_size = get_env_size(envp);
	if (create_env_list(&g->env, envp) == FAILURE)
		err_msg("An error occured with env_list", NULL, 0);
	__update_shlvl(g->env);
	if (create_exp_env_list(&g->exp_env, envp, envp_size, 0) == FAILURE)
		err_msg("An error occured with export_env_list", NULL, 0);
}
